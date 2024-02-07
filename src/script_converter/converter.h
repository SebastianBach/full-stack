#ifndef CONVERTER_H__
#define CONVERTER_H__

#include <iostream>

inline void print_error(const char* msg)
{
    std::cout << "\033[31m";
    std::cout << "Error: " << msg << std::endl;
    std::cout << "\033[0m";
}

bool converter(int argc, char* argv[]);

#endif
