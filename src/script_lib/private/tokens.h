#pragma once
#include "script.h"
#include <map>

namespace script
{

struct language_token
{
    command     ID;
    bool        has_operand;
    std::string token;
    char        byte_code;
};

static const std::vector<language_token> language_tokens = {

    {command::TEXT, true, "text", 0},
    {command::PROCESS, false, "process", 1},
    {command::PRINT, false, "print", 2},
    {command::LOAD, true, "load", 3},
    {command::SAVE, true, "save", 4}};

inline bool get_from_token(const std::string& token, language_token& res)
{
    for (const auto& t : language_tokens)
        if (t.token == token)
        {
            res = t;
            return true;
        }

    return false;
}

inline bool get_from_ID(command ID, language_token& res)
{
    for (const auto& t : language_tokens)
        if (t.ID == ID)
        {
            res = t;
            return true;
        }

    return false;
}

inline bool get_from_byte_code(char byte_code, language_token& res)
{
    for (const auto& t : language_tokens)
        if (t.byte_code == byte_code)
        {
            res = t;
            return true;
        }

    return false;
}

static const std::vector<char> secret_key = {
    static_cast<char>(0x6c), static_cast<char>(0x24), static_cast<char>(0x05),
    static_cast<char>(0x67), static_cast<char>(0x0f), static_cast<char>(0xd8),
    static_cast<char>(0x21), static_cast<char>(0xb1), static_cast<char>(0xf1),
    static_cast<char>(0x0a), static_cast<char>(0x14), static_cast<char>(0x53),
    static_cast<char>(0xe3), static_cast<char>(0x44), static_cast<char>(0x11),
    static_cast<char>(0x87)};


struct vector_hash
{
    std::size_t operator()(const std::vector<char>& v) const
    {
        std::hash<char> hasher;
        std::size_t     seed = 0;
        for (char i : v)
        {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

} // namespace script
