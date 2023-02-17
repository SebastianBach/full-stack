#include <fstream>
#include <iostream>
#include <my_func.h>
#include <string>

namespace
{
int process(const char* input, const char* output)
{
    std::cout << "Input: " << input << "\nOutput: " << output << std::endl;

    std::ifstream input_file{input};

    if (!input_file.is_open())
    {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    std::ofstream output_file{output};

    if (!output_file.is_open())
    {
        std::cerr << "Failed to open output file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(input_file, line))
    {
        func::convert2(line);
        output_file << line << std::endl;
    }

    input_file.close();
    output_file.close();

    return 0;
}
} // namespace

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Missing arguments." << std::endl;
        return -1;
    }

    return process(argv[1], argv[2]);
}
