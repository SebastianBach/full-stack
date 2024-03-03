#include "script.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <text_conversion_constexpr.h>
#include <vector>

namespace script
{

struct cmd_args
{
    std::string&                         memory;
    std::string&                         error;
    const std::string&                   operand;
    std::function<void(const char* msg)> print;
};

struct engine_command
{
    std::function<void(cmd_args& args)> func;
    const command                       cmd;
};

template <typename F>
void add_command(std::vector<engine_command>& cmds, command cmd, F&& f)
{
    cmds.emplace_back(engine_command{f, cmd});
}

void set_commands(std::vector<engine_command>& cmds)
{
    add_command(
        cmds, command::PROCESS,
        [](cmd_args& args)
        { text_conversion_constexpr::convert_to_title_case(args.memory); });

    add_command(cmds, command::INVALID,
                [](cmd_args& args) { args.error = "Invalid command"; });

    add_command(cmds, command::TEXT,
                [](cmd_args& args) { args.memory = args.operand; });

    add_command(cmds, command::PRINT,
                [](cmd_args& args)
                {
                    if (args.print)
                    {
                        args.print(args.memory.c_str());
                        return;
                    }

                    args.error =
                        "print command called, but no print callback provided";
                });

    add_command(cmds, command::LOAD,
                [](cmd_args& args)
                {
                    std::ifstream file{args.operand};

                    if (!file.is_open())
                    {
                        args.error =
                            std::string{"Could not open file "} + args.operand;
                        return;
                    }

                    args.memory.clear();

                    std::stringstream buffer;
                    buffer << file.rdbuf();
                    args.memory = buffer.str();

                    file.close();
                });

    add_command(cmds, command::SAVE,
                [](cmd_args& args)
                {
                    std::ofstream output_file{args.operand};

                    if (!output_file.is_open())
                    {
                        args.error =
                            std::string{"Could not open file "} + args.operand;
                        return;
                    }

                    output_file << args.memory << std::endl;

                    output_file.close();
                });
}

class engine::engine_impl
{
public:
    engine_impl(std::function<void(const char* msg)> print) : m_print(print)
    {
        m_commands.reserve(6);
        set_commands(m_commands);
    }

    std::string run_command(command cmd_id, const std::string& operand)
    {
        if (cmd_id == command::COMMENT)
            return "";

        for (auto& cmd : m_commands)
            if (cmd.cmd == cmd_id)
            {
                cmd_args args{m_memory, m_error, operand, m_print};
                cmd.func(args);

                if (!m_error.empty())
                    return m_error;

                return "";
            }

        return "Command not found";
    }

    std::string                          m_memory = {};
    std::string                          m_error  = {};
    std::function<void(const char* msg)> m_print;
    std::vector<engine_command>          m_commands;
};

engine::engine(std::function<void(const char* msg)> print)
    : m_impl(std::make_unique<engine_impl>(print))
{
}

engine::~engine() {}

std::string engine::run(command cmd, const std::string& operand)
{
    return m_impl->run_command(cmd, operand);
}

std::string engine::get_memory() const
{
    return m_impl->m_memory;
}

} // namespace script
