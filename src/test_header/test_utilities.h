#pragma once
#include "text_conversion_constexpr.h"

namespace test
{
template <auto N, auto A>
consteval auto compare(const char (&a)[N], const std::array<char, A>& b)
{
    static_assert(N == A + 1);

    for (auto i = 0u; i < A; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

template <auto N> consteval auto to_array(const char (&a)[N])
{
    std::array<char, N - 1> out;
    for (auto i = 0u; i < N - 1; ++i)
        out[i] = a[i];
    return out;
}

template <auto N> consteval auto test_title_case(const char (&a)[N], const char (&b)[N])
{
    auto arr = test::to_array(a);
    text_conversion_constexpr::convert_to_title_case(arr);
    return test::compare(b, arr);
}

} // namespace test
