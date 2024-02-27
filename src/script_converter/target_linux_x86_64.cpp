#include "script.h"
#include "targets.h"
#include <cstring>
#include <fstream>

namespace
{

const char* tab = "   ";
const char* nl  = "\n";

inline void add(std::vector<std::string>& commands, const std::string& cmd)
{
    commands.push_back(cmd);
}

inline void add_syscall(std::vector<std::string>& commands)
{
    commands.push_back("syscall");
}

inline void add_line(std::ofstream& stream, const char* line)
{
    stream << line << "\n";
}

struct linux_x86_64
{

    void init()
    {
        data.push_back("allocated_memory: .quad 0");
        data.push_back("allocated_memory_size: .quad 0");
    }

    void close()
    {
        _free_if_set();

        commands.push_back("# exit success");
        commands.push_back("mov $60, %rax");
        commands.push_back("xor %rdi, %rdi");
        commands.push_back("syscall");

        commands.push_back("# exit failure");
        commands.push_back("allocation_failed:");
        commands.push_back("mov $60, %rax ");
        commands.push_back("mov $1, %edi");
        commands.push_back("syscall");
    }

    void text(const std::string& text)
    {
        _free_if_set();

        commands.push_back("# text");

        const auto text_id     = "text_" + std::to_string(data_cnt);
        const auto text_length = text_id + "_len";

        {
            // add to data section

            std::string dataLine = text_id + ": .string \"" + text + "\\n\"";
            data.push_back(dataLine);

            dataLine = text_length + " = . - " + text_id;
            data.push_back(dataLine);

            data_cnt++;

            commands.push_back("lea " + text_length + "(%rip), %rax");
            commands.push_back("movq (%rax), %rax ");
            commands.push_back("movq %rax, allocated_memory_size(%rip)");
        }

        _alloc();

        {
            commands.push_back("# copy");
            commands.push_back("movq allocated_memory(%rip), %rdi");
            commands.push_back("lea " + text_id + "(%rip), %rsi");
            commands.push_back("mov $" + text_length + ", %rcx");
            commands.push_back("rep movsb ");
        }
    }

    void print()
    {
        commands.push_back("# print");

        if (!memory_set)
        {
            issues.push_back(
                {issue::TYPE::WARNING,
                 "print called without memory set, no code generated.", "...",
                 0});
            return;
        }

        commands.push_back("movq $1, %rax ");
        commands.push_back("movq $1, %rdi");
        commands.push_back("movq allocated_memory(%rip), %rsi");
        commands.push_back("movq allocated_memory_size(%rip), %rdx");
        commands.push_back("syscall");
    }

    void process()
    {
        if (!memory_set)
        {
            issues.push_back(
                {issue::TYPE::WARNING,
                 "process called without memory set, no code generated.", "...",
                 0});
            return;
        }

        commands.push_back("# process");
        commands.push_back("mov allocated_memory(%rip), %rdi ");
        commands.push_back("mov allocated_memory_size(%rip), %rsi");
        commands.push_back("call text_conversion_c");
    }

    void _alloc()
    {

        if (memory_set)
        {
            issues.push_back({issue::TYPE::ERROR,
                              "_alloc called on exiting memory", "...", 0});
            return;
        }

        commands.push_back("mov $text_0_len, %rax");
        commands.push_back("movq %rax, allocated_memory_size(%rip)");
        commands.push_back("movq $0, %rdi ");
        commands.push_back("movq allocated_memory_size(%rip), %rsi");
        commands.push_back("movq $7, %rdx");
        commands.push_back("movq $34, %r10 ");
        commands.push_back("movq $-1, %r8");
        commands.push_back("movq $0, %r9");
        commands.push_back("movq $9, %rax");
        commands.push_back("syscall");
        commands.push_back("cmpq $-1, %rax ");
        commands.push_back("je allocation_failed");
        commands.push_back("movq %rax, allocated_memory(%rip)");

        memory_set = true;
    }

    void _free_if_set()
    {
        if (memory_set)
        {
            commands.push_back("# free");
            commands.push_back("movq allocated_memory(%rip), %rdi");
            commands.push_back("movq allocated_memory_size(%rip), %rsi");
            commands.push_back("movq $11, %rax");
            commands.push_back("syscall");

            memory_set = false;
        }
    }

    std::vector<issue>&       issues;
    std::vector<std::string>& data;
    std::vector<std::string>& commands;

    bool         memory_set = false;
    unsigned int data_cnt   = 0;
};

} // namespace

bool make_linux_x86_64(std::vector<std::string>& src,
                       std::vector<issue>& issues, const char* dst)
{
    std::ofstream file_stream(dst);

    if (!file_stream.is_open())
        return false;

    std::vector<std::string> data;
    std::vector<std::string> commands;

    // parse

    linux_x86_64 machine(issues, data, commands);

    machine.init();

    for (const auto& line : src)

    {
        script::command cmd;
        std::string     operand;
        script::parse(line, cmd, operand);

        if (cmd == script::command::INVALID)
            continue;
        else if (cmd == script::command::COMMENT)
            continue;
        else if (cmd == script::command::TEXT)
        {
            machine.text(operand);
        }
        else if (cmd == script::command::PRINT)
        {
            machine.print();
        }
        else if (cmd == script::command::PROCESS)
        {
            machine.process();
        }
    }

    machine.close();

    // set return code

    // write to file

    add_line(file_stream, "# Linux x86_64 (ADM64)");
    add_line(file_stream, "# AT&T syntax");

    add_line(file_stream, ".section .data ");

    for (const auto& line : data)
        file_stream << line << nl;

    add_line(file_stream, ".section .text");
    add_line(file_stream, ".global _start");
    add_line(file_stream, "_start:");

    for (const auto& cmd : commands)
        file_stream << tab << cmd << nl;

    file_stream.close();

    return true;
}
