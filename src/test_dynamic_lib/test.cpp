#include "lib.h"
#include <iostream>

int main()
{
    std::cout << "Version: " << version() << std::endl;

    char text[] = "this is a test headline";
    title_case(text);
    std::cout << text << std::endl;

    return 0;
}
