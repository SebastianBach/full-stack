#include <cstdlib>
#include <fstream>
#include <iostream>
#include <script.h>
#include <string>
#include <vector>

inline void print_error(const char* msg)
{
    std::cout << "\033[31m";
    std::cout << "Error: " << msg << std::endl;
    std::cout << "\033[0m";
}

bool compile(int argc, char* argv[])
{
    if (argc <= 2)
    {
        print_error("Missing command line argument.");
        return false;
    }

    // todo: make option
    std::cout << argv[1] << "\n";
    std::cout << argv[2] << "\n";

    std::ifstream source{argv[1]};

    if (!source.is_open())
        return false;

    std::ofstream dst{argv[2]};
    if (!dst.is_open())
        return false;

    std::vector<std::string> lines;
    lines.reserve(16);

    std::string line;
    while (std::getline(source, line))
    {
        if ((line.back() == '\r' || line.back() == '\n'))
            line.erase(line.size() - 1);

        if (!line.empty())
            lines.push_back(line);
    }

    source.close();

    if (lines.empty())
        return false;

    std::vector<char> bytecode;
    auto              res = script::compile(lines, bytecode);

    if (!res.empty())
    {
        print_error(res.c_str());
        return false;
    }

    dst.write(bytecode.data(), bytecode.size());

    // todo: make class
    dst.close();

    return true;
}

int main(int argc, char* argv[])
{
    if (!compile(argc, argv))
        return EXIT_FAILURE;

    return EXIT_FAILURE;
}
