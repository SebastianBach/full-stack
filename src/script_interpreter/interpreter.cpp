#include "script.h"
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

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        print_error("Missing command line argument.");
        return -1;
    }

    // todo: make option
    std::cout << argv[1] << "\n";

    std::ifstream file{argv[1]};

    if (!file.is_open())
        return -1;

    script::engine  eng{print};
    script::command cmd;
    std::string     operand;

    std::string line;
    while (std::getline(file, line))
    {
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
            break;
        }

        const auto res = eng.run(cmd, operand);
        if (!res.empty())
        {
            print_error(res.c_str());
            return -1;
        }
    }

    file.close();

    return 0;
}
