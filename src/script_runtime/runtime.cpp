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

void print_info(const char* msg)
{
    std::cout << msg << std::endl;
}

auto runtime(const char* arg)
{
    std::ifstream source{arg};

    if (!source.is_open())
    {
        print_error("Could not open file.");
        return false;
    }

    const std::vector<char> data(std::istreambuf_iterator<char>(source), {});

    source.close();

    std::cout << data.size() << "\n";

    const auto res = script::runtime(data, print_info);

    if (!res.empty())
    {
        print_error(res.c_str());
        return false;
    }

    return true;
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

    if (!runtime(argv[1]))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
