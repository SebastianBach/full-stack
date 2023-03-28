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

void print_info(const char* msg)
{
    std::cout << msg << std::endl;
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

    std::ifstream source{argv[1]};

    if (!source.is_open())
    {
        print_error("Could not open file.");
        return -1;
    }

    const std::vector<char> data(std::istreambuf_iterator<char>(source), {});

    source.close();

    std::cout << data.size() << "\n";

    const auto res = script::runtime(data, print_info);

    if (!res.empty())
    {
        print_error(res.c_str());
        return -1;
    }

    return 0;
}
