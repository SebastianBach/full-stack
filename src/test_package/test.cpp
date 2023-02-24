#include "text_conversion.h"
#include <iostream>

int main() {
    std::cout << text_conversion::version() << "\n" << text_conversion::date() << std::endl;

    std::string data {"this is some headline"};
    text_conversion::convert_to_title_case(data);

    std::cout << data << std::endl;

    return 0;
}
