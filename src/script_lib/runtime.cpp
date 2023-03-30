#include "script.h"
#include "tokens.h"

namespace script
{
std::string runtime(const std::vector<char>&             bytecode,
                    std::function<void(const char* msg)> print)
{
    if (bytecode.empty())
        return "Empty source";

    const auto size = bytecode.size();

    if (size < 5)
        return "Invalid code (1)";

    // check ID
    if (bytecode.at(0) != 't')
        return "Invalid code (2)";
    if (bytecode.at(1) != 'c')
        return "Invalid code (2)";
    if (bytecode.at(2) != 'b')
        return "Invalid code (2)";
    if (bytecode.at(3) != 'c')
        return "Invalid code (2)";

    // check version
    if (bytecode.at(4) != 1)
        return "Invalid version";

    // validate

    const auto payload_offset = 5 + sizeof(size_t);

    {
        size_t stored_hash = 0;
        memcpy(&stored_hash, bytecode.data() + 5, sizeof(size_t));

        std::vector<char> hash_argument;

        std::vector<char>::const_iterator start =
            bytecode.begin() + payload_offset;
        std::vector<char>::const_iterator end = bytecode.end();

        hash_argument.insert(hash_argument.end(), start, end);

        hash_argument.insert(hash_argument.end(), secret_key.begin(),
                             secret_key.end());

        vector_hash hasher;
        const auto  hash_value = hasher(hash_argument);

        if (hash_value != stored_hash)
            return "Invalid code (3)";
    }

    std::string operand;

    engine eng{print};

    for (auto i = payload_offset; i < size; ++i)
    {
        const auto value = bytecode.at(i);

        language_token t;
        if (!get_from_byte_code(value, t))
            return "Invalid byte code";

        if (t.has_operand)
        {
            // todo: add checks

            const auto   type_size    = sizeof(unsigned int);
            auto operand_size = 0u;
            i++;
            memcpy(&operand_size, bytecode.data() + i, type_size);

            i = i + type_size;

            operand = std::string(bytecode.begin() + i,
                                  bytecode.begin() + i + operand_size);

            i = i + operand_size - 1;
        }

        const auto res = eng.run(t.ID, operand);

        if (!res.empty())
            return res;
    }

    return "";
}
} // namespace script
