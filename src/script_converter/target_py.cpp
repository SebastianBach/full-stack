#include "script.h"
#include "targets.h"
#include <cstring>
#include <fstream>

bool make_py(std::vector<std::string>& lines, const char* dst)
{
    std::ofstream file_stream(dst);

    if (!file_stream.is_open())
        return false;

    const char* tab = "   ";
    const char* nl  = "\n";

    file_stream << "import text_conversion" << nl << nl;

    file_stream << "if __name__ == '__main__':" << nl;

    for (const auto& line : lines)
    {
        script::command cmd;
        std::string     operand;
        script::parse(line, cmd, operand);

        if (cmd == script::command::INVALID)
            continue;

        if (cmd == script::command::COMMENT)
        {
            file_stream << tab << line << nl;
        }
        else if (cmd == script::command::TEXT)
        {
            file_stream << tab << "text = \"" << operand << "\"" << nl;
        }
        else if (cmd == script::command::PROCESS)
        {
            file_stream << tab << "text = text_conversion.title_case(text)"
                        << nl;
        }
        else if (cmd == script::command::PRINT)
        {
            file_stream << tab << "print(text)" << nl;
        }
        else if (cmd == script::command::SAVE)
        {
            file_stream << tab << "with open(\"" << operand
                        << "\", \"w\") as file:" << nl;
            file_stream << tab << tab << "file.write(text)" << nl;
        }
        else if (cmd == script::command::LOAD)
        {
            file_stream << tab << "with open(\"" << operand
                        << "\", 'r') as file:" << nl;
            file_stream << tab << tab << "text = file.read()" << nl;
        }
    }

    file_stream << nl;

    file_stream.close();

    return true;
}