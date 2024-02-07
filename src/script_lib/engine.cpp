#include "script.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <text_conversion_constexpr.h>
#include <vector>

namespace script
{

class engine::engine_impl
{
public:
    engine_impl(std::function<void(const char* msg)> print) : m_print(print) {}

    std::string m_memory = {};

    std::function<void(const char* msg)> m_print;

    std::string print() const
    {
        if (m_print)
            m_print(m_memory.c_str());
        else
            return "print command called, but no print callback provided";

        return "";
    }

    void process()
    {
        text_conversion_constexpr::convert_to_title_case(m_memory);
    }

    std::string load(const std::string& operand)
    {
        std::ifstream file{operand};

        if (!file.is_open())
            return std::string{"Could not open file "} + operand;

        m_memory.clear();

        std::string line;
        while (std::getline(file, line))
            m_memory += line + "\n";

        file.close();
        return "";
    }

    std::string save(const std::string& operand)
    {
        std::ofstream output_file{operand};

        if (!output_file.is_open())
            return std::string{"Could not open file "} + operand;

        output_file << m_memory << std::endl;

        output_file.close();

        return "";
    }
};

engine::engine(std::function<void(const char* msg)> print)
    : m_impl(std::make_unique<engine_impl>(print))
{
}

engine::~engine() {}

std::string engine::run(command cmd, const std::string& operand)
{
    switch (cmd)
    {
    case (command::INVALID):
    {
        return "invalid command";
        break;
    }
    case (command::COMMENT):
    {
        break;
    }
    case (command::TEXT):
    {
        m_impl->m_memory = operand;
        break;
    }
    case (command::PRINT):
    {
        return m_impl->print();
        break;
    }
    case (command::PROCESS):
    {
        m_impl->process();
        break;
    }
    case (command::LOAD):
    {
        return m_impl->load(operand);
        break;
    }
    case (command::SAVE):
    {
        return m_impl->save(operand);
        break;
    }
    }

    return "";
}

std::string engine::get_memory() const
{
    return m_impl->m_memory;
}

} // namespace script
