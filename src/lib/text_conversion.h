#ifndef _TEXT_CONVERSION_H__
#define _TEXT_CONVERSION_H__

#include <array>
#include <string>

namespace text_conversion
{
void convert_to_title_case(char* data, size_t cnt);

void convert_to_title_case(std::string& data);

#if __cplusplus >= 201703L
template <typename T, auto N> void convert_to_title_case(std::array<T, N>& data)
{
    convert_to_title_case(data.data(), data.size());
}
#else
template <typename T, int N> void convert_to_title_case(std::array<T, N>& data)
{
    convert_to_title_case(data.data(), data.size());
}
#endif

const char* version();
const char* date();

} // namespace text_conversion

#endif
