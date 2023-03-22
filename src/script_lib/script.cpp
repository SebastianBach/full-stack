#include "script.h"
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <text_conversion_constexpr.h>
#include <vector>

namespace script
{
void parse(const std::string& line, command& command, std::string& operand)
{
    command = command::INVALID;

    if (line.starts_with("#"))
    {
        command = command::COMMENT;
        return;
    }

    std::string cmd;
    std::string op;

    std::istringstream iss(line);
    iss >> cmd;

    if (cmd.empty())
        return;

    static std::map<std::string, script::command> map_command_with_operand = {
        {"text", command::TEXT},
        {"load", command::LOAD},
        {"save", command::SAVE}};

    auto res = map_command_with_operand.find(cmd);
    if (res != map_command_with_operand.end())
    {
        command = res->second;
        std::getline(iss >> std::ws, operand);
        return;
    }

    static std::map<std::string, script::command> map = {
        {"process", command::PROCESS}, {"print", command::PRINT}};

    res = map.find(cmd);
    if (res != map.end())
    {
        command = res->second;
        return;
    }
}

std::string engine::run(command cmd, const std::string& operand)
{
    switch (cmd)
    {
    case (command::COMMENT):
    {
        break;
    }
    case (command::TEXT):
    {
        m_memory = operand;
        break;
    }
    case (command::PRINT):
    {
        std::cout << m_memory << std::endl;
        break;
    }
    case (command::PROCESS):
    {
        text_conversion_constexpr::convert_to_title_case(m_memory);
        break;
    }
    case (command::LOAD):
    {
        std::ifstream file{operand};

        if (!file.is_open())
            return std::format("Could not open file {}", operand);

        m_memory.clear();

        std::string line;
        while (std::getline(file, line))
            m_memory += line + "\n";

        file.close();

        break;
    }
    case (command::SAVE):
    {
        std::ofstream output_file{operand};

        if (!output_file.is_open())
            return std::format("Could not open file {}", operand);

        output_file << m_memory << std::endl;

        output_file.close();

        break;
    }
    }

    return "";
}

std::string engine::get_memory() const
{
    return m_memory;
}

} // namespace script
