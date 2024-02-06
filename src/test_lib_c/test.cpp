#include "c_wrapper.h"
#include <cstdlib>
#include <string>
#include <vector>

int main()
{
    const std::string input{"this is the headline"};

    std::vector<char> data;
    data.assign(input.begin(), input.end());

    text_conversion_c(data.data(), data.size());

    const std::string result(data.begin(), data.end());

    const std::string expected{"This Is the Headline"};

    if (expected == result)
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}
