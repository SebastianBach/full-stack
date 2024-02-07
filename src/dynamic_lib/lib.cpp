#include "lib.h"
#include "text_conversion_constexpr.h"
#include <cstring>
#include <span>

void title_case(char* text)
{
    const auto length = std::strlen(text);

    std::span<char> temp(text, length);

    text_conversion_constexpr::convert_to_title_case(temp);
}

const char* version()
{
    return text_conversion_constexpr::version();
}
