#include <cstdlib>
#include <iostream>
#include <string>
#include <text_conversion_constexpr.h>

int main()
{
    std::string input;
    while (true)
    {
        std::cout << "Enter a text to process or \"exit\" to end the program: ";

        std::getline(std::cin, input);

        if (input == "exit")
            break;

        text_conversion_constexpr::convert_to_title_case(input);

        std::cout << input << std::endl;
    }

    std::cout << "end of program" << std::endl;

    return EXIT_SUCCESS;
}
