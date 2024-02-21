#include "text_conversion.h"
#include <cstdlib>
#include <iostream>

auto base_example()
{
    // [basic_example]

    std::string text{"this is a headline"};

    text_conversion::convert_to_title_case(text);

    std::cout << text << std::endl;

    // [basic_example]

    return text == std::string{"This Is a Headline"};
}

int main()
{
    if (!base_example())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
