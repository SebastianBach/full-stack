#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

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
    ~engine();

    std::string run(command cmd, const std::string& operand);

    std::string get_memory() const;

private:
    class engine_impl;
    std::unique_ptr<engine_impl> m_impl;
};

std::string compile(const std::vector<std::string>& source,
                    std::vector<char>&              data);

std::string runtime(const std::vector<char>&             bytecode,
                    std::function<void(const char* msg)> print);

} // namespace script
