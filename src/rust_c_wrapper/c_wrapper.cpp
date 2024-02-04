
#include "text_conversion_constexpr.h"
#include <span>

extern "C"
{
    void text_conversion_c(char* buf, size_t size)
    {
        std::span<char> temp(buf, size);
        text_conversion_constexpr::convert_to_title_case(temp);
    }
}
