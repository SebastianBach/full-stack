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

} // namespace

bool make_linux_x86_64(std::vector<std::string>& src, const char* dst)
{
    std::ofstream file_stream(dst);

    if (!file_stream.is_open())
        return false;

    std::vector<std::string> data;
    std::vector<std::string> commands;

    // parse

    auto text_cnt = 0;
    std::string current_text_id;
    std::string current_text_length;

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
            const std::string text_id = "text_" + std::to_string(text_cnt);
            const std::string text_length = text_id + "_len";

            std::string dataLine = text_id + ": .string \"" + operand + "\"";
            data.push_back(dataLine);

            dataLine = text_length + " = . - " + text_id;
            data.push_back(dataLine);

            current_text_id = text_id;
            current_text_length = text_length;

            text_cnt++;
        }
        else if (cmd == script::command::PRINT)
       {
            add(commands, "mov $1, %rax");
            add(commands, "mov $1, %rdi");
            add(commands, "lea " +current_text_id+ "(%rip), %rsi");
            add(commands, "mov $"+current_text_length+", %rdx");
            add_syscall(commands);
       } 
    }

    // set return code

    add(commands, "mov $60, %rax");
    add(commands, "xor %rdi, %rdi");
    add_syscall(commands);

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
