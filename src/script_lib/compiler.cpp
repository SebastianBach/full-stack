#include "script.h"
#include "tokens.h"
#include <format>
#include <map>

namespace script
{
std::string compile(const std::vector<std::string>& source,
                    std::vector<char>&              data)
{
    if (source.empty())
        return "Empty source";

    data.reserve(1024);

    data.push_back('t'); // text
    data.push_back('c'); // conversion
    data.push_back('b'); // byte
    data.push_back('c'); // code

    data.push_back(1); // version 1

    command     cmd;
    std::string operand;

    auto line_index = 0;
  
    for (const auto& line : source)
    {
        line_index++;

        if (line.empty())
            continue;

        parse(line, cmd, operand);

        if (cmd == command::COMMENT)
            continue;

        if (cmd == command::INVALID)
        {
            data.clear();
            return std::format("Invalid command at line {}", line_index);
        }

        const auto& token = codes.at(cmd);

        data.push_back(token.code_value);

        if (token.has_operand)
        {
            auto idx = data.size();

            // limit: only char long strings
            const auto size = (unsigned int)operand.size();
            const auto data_size = sizeof(unsigned int);

            data.resize(idx + data_size);

            memcpy(data.data() + idx, &size, data_size);

            idx = data.size();
            data.resize(idx + size);

            memcpy(data.data() + idx, operand.data(), size);

        }
    }

    return "";
}
} // namespace script
