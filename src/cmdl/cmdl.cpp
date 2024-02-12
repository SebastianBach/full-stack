#include <algorithm>
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
    if (argc == 1)
    {
        std::cout << "Missing arguments." << std::endl;
        return 1;
    }

    process(argv[1]);

    return 0;
}
