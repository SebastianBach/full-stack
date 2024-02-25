#include "converter.h"
#include "script.h"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

enum class TARGET
{
    UKNOWN,
    CPP,
    PY
};

inline TARGET to_target(const char* arg)
{
    if (std::strcmp(arg, "cpp") == 0)
        return TARGET::CPP;

    if (std::strcmp(arg, "py") == 0)
        return TARGET::PY;

    return TARGET::UKNOWN;
}

bool load_file(std::vector<std::string>& lines, const std::string& src)
{
    std::ifstream source{src};

    if (!source.is_open())
    {
        print_error("Could not open source file.");
        return false;
    }

    std::string line;
    while (std::getline(source, line))
    {
        if (line.empty())
            continue;

        if ((line.back() == '\r' || line.back() == '\n'))
            line.erase(line.size() - 1);

        lines.push_back(line);
    }

    source.close();
    return true;
}

bool make_cpp_file(std::vector<std::string>& lines, const char* dst)
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

bool make_py_file(std::vector<std::string>& lines, const char* dst)
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

bool converter(int argc, char* argv[])
{
    if (argc != 4)
    {
        print_error("Invalid command line arguments.");
        return false;
    }

    std::cout << argv[1] << "\n";
    std::cout << argv[2] << "\n";
    std::cout << argv[3] << "\n";

    const auto target = to_target(argv[3]);

    if (target == TARGET::UKNOWN)
    {
        print_error("Invalid target language argument.");
        return false;
    }

    std::vector<std::string> lines;
    if (!load_file(lines, argv[1]))
        return false;

    if (target == TARGET::CPP)
        return make_cpp_file(lines, argv[2]);
    else if (target == TARGET::PY)
        return make_py_file(lines, argv[2]);

    return true;
}
