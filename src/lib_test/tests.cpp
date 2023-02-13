#include "lib.h"
#include <iostream>

auto test(const char* input, const char* expected)
{
    std::string test{input};
    func_lib::convert_string(test);
    return test == std::string{expected};
}

int main()
{
    std::cout << func_lib::version() << "\n" << func_lib::date() << std::endl;

    if (!test("test", "test"))
        return -1;

    if (!test("TEST", "test"))
        return -1;

    if (!test("TeSt", "test"))
        return -1;

    std::array                  input    = {'T', 'e', 'S', 't'};
    static constinit std::array expected = {'t', 'e', 's', 't'};

    func_lib::convert_array(input);

    if (input != expected)
        return -1;

    return 0;
}
