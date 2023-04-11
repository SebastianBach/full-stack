#ifndef _TEXT_CONVERSION_H__
#define _TEXT_CONVERSION_H__

#include <array>
#include <string>

namespace text_conversion
{
/**
 * Converts the given text to title case.
 * Modifies the data in-place.
 *
 * @param[in,out] data    Pointer to the text to convert.
 * @param[in]     cnt     Length of the text.
 */
void convert_to_title_case(char* data, size_t cnt);

/**
 * Converts the given string to title case.
 * Modifies the data in-place.
 *
 * @param[in,out] data    std::string to convert.
 */
void convert_to_title_case(std::string& data);

#if __cplusplus >= 201703L
/**
 * Converts the given std::array to title case.
 * Modifies the data in-place.
 *
 * @param[in,out] data    std::array to convert.
 */
template <typename T, auto N> void convert_to_title_case(std::array<T, N>& data)
{
    convert_to_title_case(data.data(), N);
}
#else
/**
 * Converts the given std::array to title case.
 * Modifies the data in-place.
 *
 * @param[in,out] data    std::array to convert.
 */
template <typename T, int N> void convert_to_title_case(std::array<T, N>& data)
{
    convert_to_title_case(data.data(), N);
}
#endif

/**
 * Returns the library version.
 *
 * @return  The library version as null-terminated string.
 */
const char* version();

/**
 * Returns the library build date.
 *
 * @return  The library build date as null-terminated string.
 */
const char* date();

} // namespace text_conversion

#endif
