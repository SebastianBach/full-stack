#include "script.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline void print_error(const char* msg)
{
    std::cout << "\033[31m";
    std::cout << "Error: " << msg << std::endl;
    std::cout << "\033[0m";
}

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

bool load_file(std::vector<std::string>& lines, const char* src)
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
        if ((line.back() == '\r' || line.back() == '\n'))
            line.erase(line.size() - 1);

        if (!line.empty())
            lines.push_back(line);
    }

    source.close();
    return true;
}

bool make_cpp_file(std::vector<std::string>& lines, const char* dst)
{
    std::ofstream file_stream(dst);

    if (!file_stream.is_open())
        return false;

    for (const auto& line : lines)
        file_stream << line << "\n";

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
        if (line.empty())
        {
            file_stream << "\n";
            continue;
        }

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
                        << "\", \"w\") as text_file:" << nl;
            file_stream << tab << tab << "text_file.write(text)" << nl;
        }
    }

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

int main(int argc, char* argv[])
{
    if (!converter(argc, argv))
    {
        print_error("failure.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
