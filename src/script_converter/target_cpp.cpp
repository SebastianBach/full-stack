#include "script.h"
#include "targets.h"
#include <cstring>
#include <fstream>

bool make_cpp(std::vector<std::string>& lines, const char* dst)
{
    std::ofstream file_stream(dst);

    if (const auto is_open = file_stream.is_open(); !is_open)
        return is_open;

    const char* tab = "   ";
    const char* nl  = "\n";

    file_stream << "#include <iostream>" << nl;
    file_stream << "#include <fstream>" << nl;
    file_stream << "#include <string>" << nl;
    file_stream << "#include \"text_conversion.h\"" << nl;

    file_stream << nl;

    file_stream << "int main()" << nl;

    file_stream << "{" << nl;

    auto first_text = true;

    for (const auto& line : lines)
    {
        script::command cmd;
        std::string     operand;
        script::parse(line, cmd, operand);

        if (cmd == script::command::INVALID)
            continue;

        if (cmd == script::command::COMMENT)
        {
            file_stream << tab << "// " << line.substr(1) << nl;
        }
        else if (cmd == script::command::TEXT)
        {
            if (first_text)
            {
                first_text = false;
                file_stream << tab << "std::string text = \"" << operand
                            << "\";" << nl << nl;
            }
            else
            {
                file_stream << tab << "text = \"" << operand << "\";" << nl
                            << nl;
            }
        }
        else if (cmd == script::command::PROCESS)
        {
            file_stream << tab
                        << "text_conversion::convert_to_title_case(text);" << nl
                        << nl;
        }
        else if (cmd == script::command::PRINT)
        {
            file_stream << tab << "std::cout << text << std::endl;" << nl << nl;
        }
        else if (cmd == script::command::SAVE)
        {
            file_stream << tab << "std::ofstream(\"" << operand
                        << "\") << text;" << nl << nl;
        }
        else if (cmd == script::command::LOAD)
        {
            file_stream << tab << "{" << nl;
            file_stream
                << tab << tab
                << "const std::string "
                   "temp((std::istreambuf_iterator<char>(std::ifstream(\""
                << operand
                << "\").rdbuf())), std::istreambuf_iterator<char>());" << nl;
            file_stream << tab << tab << "text = temp;" << nl;
            file_stream << tab << "}" << nl << nl;
        }
    }

    file_stream << tab << "return 0;" << nl;
    file_stream << "}" << nl;
    file_stream << nl;

    file_stream.close();

    return true;
}