#include <algorithm>
#include <cstring>
#include <iostream>
#include <my_func.h>
#include <vector>

namespace
{
void process(char* input)
{
    const auto size = std::strlen(input);

    std::vector<char> data;
    data.resize(size + 1);

    std::copy(input, input + size, data.begin());

    func::convert2(data);

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
        return 0;
    }

    process(argv[1]);

    return 0;
}
