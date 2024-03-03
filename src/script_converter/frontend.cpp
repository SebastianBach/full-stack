#include "frontend.h"
#include "script.h"
#include "targets.h"
#include <cstring>
#include <fstream>

namespace
{

bool parse_line(const std::string& line, unsigned int number, data& data,
                bool& memory_set)
{
    script::command cmd;
    std::string     operand;

    script::parse(line, cmd, operand);

    switch (cmd)
    {
    case (script::command::INVALID):

        data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                       "Invalid line.", line, number);

        return false;
        break;

    case (script::command::COMMENT):
    {
        auto arg = line;
        arg.erase(0, 1);

        data.add_cmd(intermediate::cmd::comment, arg, line, number);
        break;
    }
    case (script::command::TEXT):
    {
        data.add_cmd(intermediate::cmd::text_memory, operand, line, number);
        memory_set = true;
        break;
    }
    case (script::command::PRINT):
    {
        if (!memory_set)
        {
            data.add_issue(
                issue::type::WARNING, issue::phase::PARSING,
                "calling 'print' before setting memory. Line removed", line,
                number);
        }
        else
        {
            data.add_cmd(intermediate::cmd::print_memory, operand, line,
                         number);
        }

        break;
    }
    case (script::command::PROCESS):
    {

        if (memory_set)
            data.add_cmd(intermediate::cmd::process_memory, "", line, number);
        else
            data.add_issue(
                issue::type::WARNING, issue::phase::PARSING,
                "calling 'process' before setting memory. Line removed", line,
                number);

        break;
    }
    case (script::command::LOAD):
    {
        if (operand.empty())
        {
            data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                           "No operand given for 'load'.", line, number);
            return false;
        }

        data.add_cmd(intermediate::cmd::load_memory, operand, line, number);

        memory_set = true;

        break;
    }
    case (script::command::SAVE):
    {
        if (operand.empty())
        {
            data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                           "No operand given for 'save'.", line, number);
            return false;
        }

        if (memory_set)
            data.add_cmd(intermediate::cmd::save_memory, operand, line, number);
        else
            data.add_cmd(intermediate::cmd::create_file, operand, line, number);

        break;
    }
    default:
    {
        data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                       "Unknown command.", line, number);

        return false;
        break;
    }
    }

    return true;
}

} // namespace

void parse_source(const std::string& src, data& data)
{

    std::ifstream source{src};

    if (!source.is_open())
    {
        data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                       "Could not open file.", src, 0);
        data.success = false;
        return;
    }

    auto lineNumber = 0;
    auto memory_set = false;

    std::string line;
    while (std::getline(source, line))
    {
        lineNumber++;

        if (line.empty())
            continue;

        if ((line.back() == '\r' || line.back() == '\n'))
            line.erase(line.size() - 1);

        if (!parse_line(line, lineNumber, data, memory_set))
            return;
    }

    source.close();
}
