#include "lib.h"
#include <iostream>

int main() {
    std::cout << func_lib::version() << "\n" << func_lib::date() << std::endl;
    return 0;
}
