#pragma once
#include "text_conversion_constexpr.h"

namespace test
{
/*
 * Compares the C-style string with the std::array.
 *
 * @param[in] ref     Reference string.
 * @param[in] res     std::array with the conversion result.
 * @return            True if match, otherwise false.
 */
template <auto N, auto A>
consteval auto compare(const char (&a)[N], const std::array<char, A>& b)
{
    static_assert(N == A + 1);

    for (auto i = 0u; i < A; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

/*
 * Copies the C-style to a std::array.
 *
 * @param[in] a     Input text.
 * @return          The std::array copy.
 */
template <auto N> consteval auto to_array(const char (&a)[N])
{
    std::array<char, N - 1> out;
    for (auto i = 0u; i < N - 1; ++i)
        out[i] = a[i];
    return out;
}

/*
 * Tests the convert_to_title_case() function.
 *
 * @param[in] input   Input text.
 * @param[in] ref     Expected result
 * @return            True if the created result matches the expected result.
 */
template <auto N>
consteval auto test_title_case(const char (&input)[N], const char (&ref)[N])
{
    auto arr = test::to_array(input);
    text_conversion_constexpr::convert_to_title_case(arr);
    return test::compare(ref, arr);
}

} // namespace test
