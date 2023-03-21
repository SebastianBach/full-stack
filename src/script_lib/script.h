#pragma once
#include <string>

namespace script
{
enum class command
{
    TEXT,
    LOAD,
    PROCESS,
    PRINT,
    SAVE,
    COMMENT,
    INVALID
};

void parse(const std::string& line, command& command, std::string& operand);

class engine
{
public:
    std::string run(command cmd, const std::string& operand);

    std::string get_memory() const;

private:
    std::string m_memory = {};
};

} // namespace script
