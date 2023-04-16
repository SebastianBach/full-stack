#include "text_conversion.h"
#include <iostream>
#include <string>

int main()
{
    std::string text{"this is the headline"};

    text_conversion::convert_to_title_case(text);

    std::cout << text << std::endl;

    return 0;
}
