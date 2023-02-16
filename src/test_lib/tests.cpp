#include "lib.h"
#include <iostream>

inline auto test(const char* input, const char* expected)
{
    std::string test{input};
    func_lib::convert_string(test);
    return test == std::string{expected};
}

#define STR_EQ(A, B) if (!test(A,B)) return -1;

int main()
{
    std::cout << func_lib::version() << "\n" << func_lib::date() << std::endl;

    STR_EQ("test", "test");
    STR_EQ("TEST", "test");
    STR_EQ("TeSt", "test");

    std::array                  input    = {'T', 'e', 'S', 't'};
    static constinit std::array expected = {'t', 'e', 's', 't'};

    func_lib::convert_array(input);

    if (input != expected)
        return -1;

    return 0;
}
