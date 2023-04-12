#include "text_conversion.h"
#include <iostream>

int main()
{
    // [basic_example]

    std::string text{"this is a headline"};

    text_conversion::convert_to_title_case(text);

    std::cout << text << std::endl;

    // [basic_example]
}
