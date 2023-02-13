#include <my_func.h>
#include <iostream>
#include <string>

int main()
{
    std::string input;
    while (true)
    {
        std::cout << "Enter a text to process or \"exit\" to end the program: ";
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        func::convert2(input);

        std::cout << input << std::endl;
    }

    std::cout << "end of program" << std::endl;
    return 0;
}
