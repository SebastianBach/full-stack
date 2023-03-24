#include "script.h"
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <text_conversion_constexpr.h>
#include <vector>
#include "tokens.h"

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

    const auto res = tokens.find(cmd);
    if (res != tokens.end())
    {
        command = res->second.cmd;
        if (res->second.has_operand)
            std::getline(iss >> std::ws, operand);
        return;
    }
}
} // namespace script
