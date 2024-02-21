#include "text_conversion.h"
#include <cstdlib>
#include <iostream>

inline auto test(const char* input, const char* expected)
{
    std::string test{input};
    text_conversion::convert_to_title_case(test);
    return test == std::string{expected};
}

#define STR_EQ(A, B)                                                           \
    std::cout << A << " --> " B << std::endl;                                  \
    if (!test(A, B))                                                           \
        return EXIT_FAILURE;

int main()
{
    std::cout << text_conversion::version() << "\n"
              << text_conversion::date() << std::endl;

    STR_EQ("test", "Test");
    STR_EQ("this is the headline", "This Is the Headline");

    std::array                  input    = {'t', 'e', 's', 't'};
    static constinit std::array expected = {'T', 'e', 's', 't'};

    text_conversion::convert_to_title_case(input);

    if (input != expected)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
