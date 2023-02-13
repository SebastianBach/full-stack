#pragma once

#include <array>
#include <span>

namespace func
{
template <auto N> constexpr auto convert(const std::array<char, N>& input)
{
    std::array<char, N> out;

    for (auto i = 0u; i < N; ++i)
    {
        const auto& letter = input[i];
        if (letter >= 65 && letter <= 90)
            out[i] = letter + 32;
        else
            out[i] = letter;
    }

    return out;
}

template <typename DATA> constexpr void convert2(DATA& data)
{
    // const auto size = data.size();

    for (auto& letter : data)
        if (letter >= 65 && letter <= 90)
            letter = letter + 32;
}

} // namespace func
