#pragma once
#include "text_conversion_constexpr.h"
#include <string>

namespace test
{
/*
 * Tests the convert_to_title_case() function.
 *
 * @param[in] input   Input text.
 * @param[in] ref     Expected result
 * @return            True if the created result matches the expected result.
 */
template <std::size_t N>
consteval auto test_title_case(const char (&input)[N], const char (&ref)[N])
{
    constexpr std::size_t length = N - 1;

    std::array<char, length> data{};
    std::copy_n(input, length, data.begin());

    text_conversion_constexpr::convert_to_title_case(data);

    return std::equal(data.begin(), data.end(), ref);
}

} // namespace test
