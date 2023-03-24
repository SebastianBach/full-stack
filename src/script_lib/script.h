#pragma once
#include <string>
#include <functional>

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

    engine(std::function<void(const char* msg)> print);

    std::string run(command cmd, const std::string& operand);

    std::string get_memory() const;

private:
    std::string m_memory = {};

    std::function<void(const char* msg)> m_print;
};

std::string compile(const std::vector<std::string>& source,
                    std::vector<char>&              data);

} // namespace script
