#include "script.h"
#include <iostream>
#include <string>

int main()
{
    script::engine  eng;
    script::command cmd;
    std::string     operand;

    std::cout << "Enter a text to process or \"exit\" to end the program:\n";

    std::string input;
    while (true)
    {
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        script::parse(input, cmd, operand);

        if (cmd == script::command::INVALID)
        {
            std::cout << "\033[31m";
            std::cout << "invalid command" << std::endl;
            std::cout << "\033[0m";
            continue;
        }

        const auto res = eng.run(cmd, operand);

        if (!res.empty())
        {
            std::cout << "\033[31m";
            std::cout << res << std::endl;
            std::cout << "\033[0m";
            continue;
        }

        std::cout << "\033[32m";
        std::cout << "success" << std::endl;
        std::cout << "\033[0m";
    }

    return 0;
}
