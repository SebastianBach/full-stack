#include "text_conversion.h"
#include <iostream>

int main() {
    std::cout << text_conversion::version() << "\n" << text_conversion::date() << std::endl;
    return 0;
}
