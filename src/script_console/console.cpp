#include "script.h"
#include <csignal>
#include <iostream>
#include <string>

volatile std::sig_atomic_t g_signal_status;

void signal_handler(int signal)
{
    g_signal_status = signal;
}

int main()
{
    std::signal(SIGINT, signal_handler);

    auto print = [](const char* msg)
    {
        std::cout << "\033[32m";
        std::cout << msg << std::endl;
        std::cout << "\033[0m";
    };

    script::engine  eng{print};
    script::command cmd;
    std::string     operand;

    std::cout << "Enter a text to process or \"exit\" to end the program:\n";

    std::string input;
    while (true)
    {
        if (g_signal_status != 0)
            break;

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

        std::cout << "\033[34m";
        std::cout << "success" << std::endl;
        std::cout << "\033[0m";
    }

    return 0;
}
