#include "text_conversion.h"
#include "text_conversion_constexpr.h"
#include <span>

namespace text_conversion
{
void convert_to_title_case(std::string& data)
{
    text_conversion_constexpr::convert_to_title_case(data);
}

void convert_to_title_case(char* data, size_t cnt)
{
    std::span<char> temp(data, cnt);
    text_conversion_constexpr::convert_to_title_case(temp);
}

} // namespace text_conversion
