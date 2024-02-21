#include "script.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

inline void print_error(const char* msg)
{
    std::cout << "\033[31m";
    std::cout << "Error: " << msg << std::endl;
    std::cout << "\033[0m";
}

inline void print_command(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void print(const char* msg)
{
    std::cout << "\033[32m";
    std::cout << msg << std::endl;
    std::cout << "\033[0m";
}

auto run_interpreter(const std::string& arg)
{
    std::filesystem::path path(arg);

    if (!path.is_absolute())
        path = std::filesystem::absolute(path);

    std::ifstream file{path};

    if (!file.is_open())
        return false;

    script::engine  eng{print};
    script::command cmd;
    std::string     operand;

    std::string line;
    while (std::getline(file, line))
    {
        if ((line.back() == '\r' || line.back() == '\n'))
            line.erase(line.size() - 1);

        if (line.empty())
            continue;

        script::parse(line, cmd, operand);

        // todo: make argument to print comments on demand
        if (cmd == script::command::COMMENT)
            continue;

        // todo: make option
        print_command(line);

        if (cmd == script::command::INVALID)
        {
            print_error("invalid command");
            return false;
        }

        const auto res = eng.run(cmd, operand);
        if (!res.empty())
        {
            print_error(res.c_str());
            return false;
        }
    }

    file.close();

    return true;
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        print_error("Missing command line argument.");
        return EXIT_FAILURE;
    }

    // todo: make option
    std::cout << argv[1] << "\n";

    if (!run_interpreter(argv[1]))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
