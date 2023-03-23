#include "script.h"
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <text_conversion_constexpr.h>
#include <vector>

namespace script
{

engine::engine(std::function<void(const char* msg)> print) : m_print(print) {}

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
        if (m_print)
            m_print(m_memory.c_str());

        break;
    }
    case (command::PROCESS):
    {
        text_conversion_constexpr::convert_to_title_case(m_memory);
        break;
    }
    case (command::LOAD):
    {
        std::ifstream file{operand};

        if (!file.is_open())
            return std::format("Could not open file {}", operand);

        m_memory.clear();

        std::string line;
        while (std::getline(file, line))
            m_memory += line + "\n";

        file.close();

        break;
    }
    case (command::SAVE):
    {
        std::ofstream output_file{operand};

        if (!output_file.is_open())
            return std::format("Could not open file {}", operand);

        output_file << m_memory << std::endl;

        output_file.close();

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
