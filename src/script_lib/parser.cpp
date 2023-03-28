#include "script.h"
#include "tokens.h"
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

    std::istringstream iss(line);
    iss >> cmd;

    if (cmd.empty())
        return;

    language_token t;
    if (!get_from_token(cmd, t))
        return;

    command = t.ID;

    if (t.has_operand)
        std::getline(iss >> std::ws, operand);
}
} // namespace script
