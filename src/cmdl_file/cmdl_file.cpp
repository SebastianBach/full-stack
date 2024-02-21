#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <text_conversion_constexpr.h>

namespace
{
/*
 * Processes the text of the given intput file.
 *
 * @param[in] input    Path to the input text file to read data from.
 * @param[in] output   Path to the output text file to write results to.
 * @return             true if the process succeeded, otherwise false.
 */
auto process(const char* input, const char* output)
{
    std::cout << "Input: " << input << "\nOutput: " << output << std::endl;

    std::ifstream input_file{input};

    if (!input_file.is_open())
    {
        std::cerr << "Failed to open input file." << std::endl;
        return false;
    }

    std::ofstream output_file{output};

    if (!output_file.is_open())
    {
        std::cerr << "Failed to open output file" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(input_file, line))
    {
        text_conversion_constexpr::convert_to_title_case(line);
        output_file << line << std::endl;
    }

    input_file.close();
    output_file.close();

    return true;
}
} // namespace

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Invalid command line arguments." << std::endl;
        return EXIT_FAILURE;
    }

    if (!process(argv[1], argv[2]))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
