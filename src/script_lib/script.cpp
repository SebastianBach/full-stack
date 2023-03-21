#include "script.h"

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

    if (cmd == "TEXT")
    {
        command = command::TEXT;
        std::getline(iss >> std::ws, operand);
        return;
    }
    else if (cmd == "LOAD")
    {
        command = command::LOAD;
        std::getline(iss >> std::ws, operand);
        return;
    }
    else if (cmd == "SAVE")
    {
        command = command::SAVE;
        std::getline(iss >> std::ws, operand);
        return;
    }

    static std::map<std::string, script::command> map = {
        {"PROCESS", command::PROCESS}, {"PRINT", command::PRINT}};

    auto res = map.find(cmd);
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
    }

    return "";
}

std::string engine::get_memory() const
{
    return m_memory;
}

} // namespace script
