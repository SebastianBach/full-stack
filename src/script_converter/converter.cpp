#include "converter.h"
#include "script.h"
#include "targets.h"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

enum class TARGET
{
    UKNOWN,
    CPP,
    PY,
    LINUX_X86_64
};

inline TARGET to_target(const char* arg)
{
    if (std::strcmp(arg, "cpp") == 0)
        return TARGET::CPP;

    if (std::strcmp(arg, "py") == 0)
        return TARGET::PY;

    if (std::strcmp(arg, "linux_x86_64") == 0)
        return TARGET::LINUX_X86_64;

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

bool converter(int argc, char* argv[], std::vector<issue>& issues)
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
        return make_cpp(lines, argv[2]);
    else if (target == TARGET::PY)
        return make_py(lines, argv[2]);
    else if (target == TARGET::LINUX_X86_64)
        make_linux_x86_64(lines, issues, argv[2]);


    return true;
}
