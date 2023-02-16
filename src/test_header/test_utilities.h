#pragma once
#include "my_func.h"

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

template <auto N> consteval auto test(const char (&a)[N], const char (&b)[N])
{
    const auto arr = to_array(a);
    const auto res = func::convert(arr);
    return compare(b, res);
}

template <auto N> consteval auto test2(const char (&a)[N], const char (&b)[N])
{
    auto arr = test::to_array(a);
    func::convert2(arr);
    return test::compare(b, arr);
}
} // namespace test
