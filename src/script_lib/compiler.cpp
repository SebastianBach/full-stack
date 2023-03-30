#include "script.h"
#include "tokens.h"
#include <cstring>
#include <functional>
#include <map>

namespace script
{
std::string compile(const std::vector<std::string>& source,
                    std::vector<char>&              data)
{
    if (source.empty())
        return "Empty source";

    // text conversion byte code, version 1
    std::vector<char> header{'t', 'c', 'b', 'c', 1};

    std::vector<char> payload;
    payload.reserve(1024);

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
            return std::string{"Invalid command at line "} +
                   std::to_string(line_index);

        language_token t;
        if (!get_from_ID(cmd, t))
            return "Unknown command.";

        payload.push_back(t.byte_code);

        if (t.has_operand)
        {
            auto idx = payload.size();

            // limit: only char long strings
            const auto size      = static_cast<unsigned int>(operand.size());
            const auto data_size = sizeof(unsigned int);

            payload.resize(idx + data_size);

            memcpy(payload.data() + idx, &size, data_size);

            idx = payload.size();
            payload.resize(idx + size);

            memcpy(payload.data() + idx, operand.data(), size);
        }
    }

    // hash

    auto hash_argument = payload;
    hash_argument.insert(hash_argument.end(), secret_key.begin(),
                         secret_key.end());

    vector_hash hasher;
    const auto  hash_value = hasher(hash_argument);

    // merge

    data.clear();

    data.insert(data.begin(), header.begin(), header.end());

    data.resize(data.size() + sizeof(size_t));
    memcpy(data.data() + 5, &hash_value, sizeof(size_t));

    data.insert(data.end(), payload.begin(), payload.end());

    return "";
}
} // namespace script
