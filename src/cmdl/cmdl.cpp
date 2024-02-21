#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <text_conversion_constexpr.h>
#include <vector>

namespace
{
void process(const char* input)
{
    const auto size = std::strlen(input);

    std::vector<char> data;
    data.resize(size + 1);

    std::copy(input, input + size, data.begin());

    text_conversion_constexpr::convert_to_title_case(data);

    // null terminated string
    data[size] = 0;

    std::cout << data.data() << std::endl;
}
} // namespace

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid command line arguments." << std::endl;
        return EXIT_FAILURE;
    }

    process(argv[1]);

    return EXIT_SUCCESS;
}
