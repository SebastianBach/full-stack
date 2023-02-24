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
 * @return             0 if the processing succeeds, otherwise an error code.
 */
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
        return 2;
    }

    std::string line;
    while (std::getline(input_file, line))
    {
        text_conversion_constexpr::convert_to_title_case(line);
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
