#include "data.h"

#include <tuple>

namespace
{
struct asm_file
{
    std::vector<std::string> data;

    std::vector<std::string> lines;

    bool         need_memory   = false;
    bool         exit_failure  = false;
    unsigned int data_cnt      = 0;
    bool         need_new_line = false;
};

// free memory stored at allocated_memory
// after call, allocated_memory_size is 0
inline void _free_memory(std::vector<std::string>& lines)
{
    lines.push_back("# free memory");
    lines.push_back("movq allocated_memory(%rip), %rdi");
    lines.push_back("movq allocated_memory_size(%rip), %rsi");
    lines.push_back("movq $11, %rax");
    lines.push_back("syscall");
    lines.push_back("movq $0, allocated_memory_size(%rip)");
}

// alloc memory of size stored in allocated_memory_size
// after success, memory address is stored in allocated_memory
inline void _alloc_memory(std::vector<std::string>& lines)
{
    lines.push_back("movq $0, %rdi ");
    lines.push_back("movq allocated_memory_size(%rip), %rsi");
    lines.push_back("movq $7, %rdx");
    lines.push_back("movq $34, %r10 ");
    lines.push_back("movq $-1, %r8");
    lines.push_back("movq $0, %r9");
    lines.push_back("movq $9, %rax");
    lines.push_back("syscall");

    lines.push_back("cmpq $-1, %rax ");
    lines.push_back("je exit_failure");

    lines.push_back("movq %rax, allocated_memory(%rip)");
}

inline std::tuple<std::string, std::string> get_new_text(asm_file& file)
{
    const auto text_id     = "text_" + std::to_string(file.data_cnt);
    const auto text_length = text_id + "_len";

    file.data_cnt += 1;

    return {text_id, text_length};
}

inline void _print_stdout(asm_file& file)
{
    file.lines.push_back("mov $1, %rax");
    file.lines.push_back("mov $1, %rdi");
    file.lines.push_back("syscall");
}

inline void _print_new_line(asm_file& file)
{
    file.lines.push_back("lea new_line(%rip), %rsi");
    file.lines.push_back("mov $new_line_length, %rdx");
    _print_stdout(file);

    file.need_new_line = true;
}

inline void add_new_line(asm_file& file)
{
    file.data.push_back("new_line: .string \"\\n\"");
    file.data.push_back("new_line_length = . - new_line");
}

inline void generate_linux_x86_64_asm(const intermediate& i, asm_file& file)
{
    file.lines.push_back("# " + i.line);

    switch (i.command)
    {
    case (intermediate::cmd::comment):
    {
        file.lines.push_back("#" + i.operand);
        break;
    }

    case (intermediate::cmd::process_memory):
    {
        file.lines.push_back("mov allocated_memory(%rip), %rdi");
        file.lines.push_back("mov allocated_memory_size(%rip), %rsi");
        file.lines.push_back("call text_conversion_c");

        file.need_memory = true;

        break;
    }
    case (intermediate::cmd::print_text):
    {
        const auto [text_id, text_length] = get_new_text(file);

        file.data.push_back(text_id + ": .string \"" + i.operand + "\\n\"");
        file.data.push_back(text_length + " = . - " + text_id);

        file.lines.push_back("lea " + text_id + "(%rip), %rsi");
        file.lines.push_back("mov $" + text_length + ", %rdx");

        _print_stdout(file);

        break;
    }

    case (intermediate::cmd::print_memory):
    {
        file.lines.push_back("movq allocated_memory(%rip), %rsi");
        file.lines.push_back("movq allocated_memory_size(%rip), %rdx");

        _print_stdout(file);

        _print_new_line(file);

        file.need_memory   = true;
     
        break;
    }

    case (intermediate::cmd::text_memory):
    {
        _free_memory(file.lines);
    }
        [[fallthrough]];
    case (intermediate::cmd::text_init_memory):
    {
        const auto [text_id, text_length] = get_new_text(file);

        file.data.push_back(text_id + ": .string \"" + i.operand + "\"");
        file.data.push_back(text_length + " = . - " + text_id);

        file.lines.push_back("mov $" + text_length + ", %rax");
        file.lines.push_back("movq %rax, allocated_memory_size(%rip)");

        _alloc_memory(file.lines);

        file.lines.push_back("# copy");
        file.lines.push_back("movq allocated_memory(%rip), %rdi");
        file.lines.push_back("lea " + text_id + "(%rip), %rsi");
        file.lines.push_back("mov $" + text_length + ", %rcx");
        file.lines.push_back("rep movsb");

        file.exit_failure = true;
        file.need_memory  = true;

        break;
    }

    case (intermediate::cmd::create_file):
    {
        const auto [text_id, text_length] = get_new_text(file);

        file.data.push_back(text_id + ": .string \"" + i.operand + "\"");
        // file.data.push_back(text_length + " = . - " + text_id);

        file.lines.push_back("# create file");

        file.lines.push_back("mov $2, %rax");
        file.lines.push_back("lea " + text_id + "(%rip), %rdi");
        file.lines.push_back("mov $577, %rsi");
        file.lines.push_back("mov $0644, %rdx");
        file.lines.push_back("syscall");

        file.lines.push_back("cmpq $-1, %rax");
        file.lines.push_back("je exit_failure");

        file.lines.push_back("mov %rax, %rdi");
        file.lines.push_back("mov $3, %rax");
        file.lines.push_back("syscall");

        break;
    }

    case (intermediate::cmd::save_memory):
    {
        const auto [file_name_id, text_length] = get_new_text(file);

        // file name
        file.data.push_back(file_name_id + ": .string \"" + i.operand + "\"");
        //file.data.push_back(text_length + " = . - " + file_name_id);

        // create file
        file.lines.push_back("mov $2, %rax ");
        file.lines.push_back("lea " + file_name_id + "(%rip), %rdi");
        file.lines.push_back("mov $0101, %rsi");
        file.lines.push_back("mov $0644, %rdx");
        file.lines.push_back("syscall");

        file.lines.push_back("cmpq $-1, %rax");
        file.lines.push_back("je exit_failure");

        // write to file
        file.lines.push_back("mov %rax, %rdi");
        file.lines.push_back("mov $1, %rax ");
        file.lines.push_back("movq allocated_memory(%rip), %rsi");
        file.lines.push_back("movq allocated_memory_size(%rip), %rdx");
        file.lines.push_back("syscall");
        // close file
        file.lines.push_back("mov $3, %rax");
        file.lines.push_back("syscall");

        file.need_memory  = true;
        file.exit_failure = true;

        break;
    }

    case (intermediate::cmd::save_text):
    {
        const auto [text_id, text_length]           = get_new_text(file);
        const auto [file_name_id, file_name_length] = get_new_text(file);

        // file name
        file.data.push_back(file_name_id + ": .string \"" + i.operandB + "\"");
        // file.data.push_back(file_name_length + " = . - " + file_name_id);
        // text
        file.data.push_back(text_id + ": .string \"" + i.operand + "\"");
        file.data.push_back(text_length + " = . - " + text_id);
        // create file
        file.lines.push_back("mov $2, %rax ");
        file.lines.push_back("lea " + file_name_id + "(%rip), %rdi");
        file.lines.push_back("mov $0101, %rsi");
        file.lines.push_back("mov $0644, %rdx");
        file.lines.push_back("syscall");

        file.lines.push_back("cmpq $-1, %rax");
        file.lines.push_back("je exit_failure");

        // write to file
        file.lines.push_back("mov %rax, %rdi");
        file.lines.push_back("mov $1, %rax ");
        file.lines.push_back("lea " + text_id + "(%rip), %rsi");
        file.lines.push_back("mov $" + text_length + ", %rdx");
        file.lines.push_back("syscall");
        // close file
        file.lines.push_back("mov $3, %rax");
        file.lines.push_back("syscall");

        file.need_memory  = true;
        file.exit_failure = true;
        break;
    }
    case (intermediate::cmd::load_memory):
    {
        _free_memory(file.lines);
    }
        [[fallthrough]];
    case (intermediate::cmd::load_init_memory):
    {
        const auto [file_name_id, file_name_length] = get_new_text(file);

        // file name
        file.data.push_back(file_name_id + ": .string \"" + i.operand + "\"");
        //file.data.push_back(file_name_length + " = . - " + file_name_id);

        file.lines.push_back("movq $2, %rax");
        file.lines.push_back("lea " + file_name_id + "(%rip), %rdi");
        file.lines.push_back("movq $0, %rsi");
        file.lines.push_back("syscall");

        file.lines.push_back("cmpq $-1, %rax");
        file.lines.push_back("je exit_failure");

        file.lines.push_back("movq %rax, %rdi");
        file.lines.push_back("movq %rax, %rbx");

        // file size

        file.lines.push_back("# file size");
        file.lines.push_back("movq $5, %rax");
        file.lines.push_back("subq $128, %rsp");
        file.lines.push_back("movq %rsp, %rsi ");
        file.lines.push_back("syscall");

        file.lines.push_back("movq 48(%rsp), %rdx");
        file.lines.push_back("movq %rdx, allocated_memory_size(%rip)");

        _alloc_memory(file.lines);

        // read data into memory
        file.lines.push_back("# read data into memory");
        file.lines.push_back("movq $0, %rax");
        file.lines.push_back("movq %rbx, %rdi");
        file.lines.push_back("movq allocated_memory(%rip), %rsi");
        file.lines.push_back("movq allocated_memory_size(%rip), %rdx");
        file.lines.push_back("syscall");

        // close file
        file.lines.push_back("# close file");
        file.lines.push_back("mov $3, %rax");
        file.lines.push_back("syscall");

        file.need_memory  = true;
        file.exit_failure = true;

        break;
    }
    }

    file.lines.push_back("");
}

} // namespace

void generate_linux_x86_64(data& data)
{
    asm_file file;

    for (const auto& i : data.c)
        generate_linux_x86_64_asm(i, file);

    if (file.need_new_line)
        add_new_line(file);

    if (file.need_memory)
        _free_memory(file.lines);

    if (file.exit_failure)
    {
        file.data.push_back("text_failure: .string \"an error occured\"");
        file.data.push_back("text_failure_len = . -  text_failure");
    }

    // exit success
    file.lines.push_back("mov $60, %rax");
    file.lines.push_back("xor %rdi, %rdi");
    file.lines.push_back("syscall");

    // ---

    data.result.push_back("# Linux x86_64 AMD64");
    data.result.push_back("# AT&T syntax");

    data.result.push_back(".section .data");

    if (file.need_memory)
    {
        data.result.push_back("allocated_memory: .quad 0");
        data.result.push_back("allocated_memory_size: .quad 0");
    }

    for (const auto& d : file.data)
    {
        data.result.push_back(d);
    }

    data.result.push_back(".section .text");

    data.result.push_back(".global _start");
    data.result.push_back("_start:");

    for (const auto& l : file.lines)
    {
        data.result.push_back(l);
    }

    if (file.exit_failure)
    {
        data.result.push_back("");
        data.result.push_back("exit_failure:");

        if (file.need_memory)
            _free_memory(data.result);

        data.result.push_back("lea text_failure(%rip), %rsi");
        data.result.push_back("mov $text_failure_len, %rdx");
        data.result.push_back("mov $1, %rax");
        data.result.push_back("mov $1, %rdi");
        data.result.push_back("syscall");

        data.result.push_back("mov $60, %rax");
        data.result.push_back("mov $1, %edi");
        data.result.push_back("syscall");
    }

    data.result.push_back("\n");
}
