#include "script.h"
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

volatile std::sig_atomic_t g_signal_status;

void signal_handler(int signal)
{
    g_signal_status = signal;
}

inline void print_data(const char* msg)
{
    std::cout << "\033[32m";
    std::cout << msg << std::endl;
    std::cout << "\033[0m";
}

inline void print_error(const char* msg)
{
    std::cout << "\033[31m";
    std::cout << msg << std::endl;
    std::cout << "\033[0m";
}

inline void print_success()
{
    std::cout << "\033[34m";
    std::cout << "success" << std::endl;
    std::cout << "\033[0m";
}

int main()
{
    std::signal(SIGINT, signal_handler);

    script::engine  eng{print_data};
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
            print_error("invalid command");
            continue;
        }

        const auto res = eng.run(cmd, operand);

        if (!res.empty())
        {
            print_error(res.c_str());
            continue;
        }

        print_success();
    }

    return EXIT_SUCCESS;
}
