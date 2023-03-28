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

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        print_error("Missing command line argument.");
        return -1;
    }

    // todo: make option
    std::cout << argv[1] << "\n";
    std::cout << argv[2] << "\n";

    std::ifstream source{argv[1]};

    if (!source.is_open())
        return -1;

    std::ofstream dst{argv[2]};
    if (!dst.is_open())
        return -1;

    std::vector<std::string> lines;
    lines.reserve(16);

    std::string line;
    while (std::getline(source, line))
        if (!line.empty())
            lines.push_back(line);

    if (lines.empty())
        return -1;

    std::vector<char> bytecode;
    auto res = script::compile(lines, bytecode);

    if (!res.empty())
    {
        print_error(res.c_str());
        return -1;
    }

    dst.write(bytecode.data(), bytecode.size());

    // todo: make class
    source.close();
    dst.close();

    return 0;
}
