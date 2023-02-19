#pragma once

#include <array>
#include <concepts>
#include <cstring>
#include <ranges>

namespace text_conversion_constexpr
{
// https://apastyle.apa.org/style-grammar-guidelines/capitalization/title-case
template <typename DATA>
requires std::ranges::sized_range<DATA>
constexpr void convert_to_title_case(DATA& data)
{
    const auto size = data.size();
    if (size == 0)
        return;

    auto is_upper = [](const auto& letter)
    { return letter >= 65 && letter <= 90; };

    auto is_lower = [](const auto& letter)
    { return letter >= 97 && letter <= 122; };

    auto is_letter = [&](const auto& letter)
    { return is_upper(letter) || is_lower(letter); };

    auto make_upper = [](auto& letter) { letter -= 32; };

    auto strlen_constexpr = [](const char* word)
    {
        auto len = 0u;
        while (*word != '\0')
        {
            word = word + 1;
            len++;
        }
        return len;
    };

    auto comp_str = [](const char* word_a, auto& d, auto length)
    {
        for (auto i = 0u; i < length; ++i)
            if (word_a[i] != d[i])
                return false;
        return true;
    };

    auto write_word = [&](DATA& data, auto offset, auto& word, auto word_length,
                          auto to_upper)
    {
        if (to_upper && is_lower(data[offset]))
            make_upper(data[offset]);
    };

    auto check_if_short_word =
        [&](auto& word, auto word_length, const auto& short_words)
    {
        for (const auto* short_word : short_words)
        {
            const auto len = strlen_constexpr(short_word);
            if (len == word_length)
            {
                if (comp_str(short_word, word, word_length))
                    return true;
            }
        }
        return false;
    };

    const auto short_words = {"a",   "an",  "the", "and", "as", "but",
                              "for", "if",  "nor", "or",  "so", "yet",
                              "at",  "by",  "for", "in",  "of", "off",
                              "on",  "per", "to",  "up",  "via"};

    std::array<long int, 50> word;
    auto                     word_index  = 0u;
    auto                     start_index = 0u;

    // first letter
    if (is_lower(data[0]))
        make_upper(data[0]);

    const auto end_index      = size - 1u;
    auto       prev_separator = false;

    for (auto i = 0u; i < size; ++i)
    {
        const auto letter = is_letter(data[i]);
        if (letter)
        {
            if (word_index == 0u)
                start_index = i;

            word[word_index] = data[i];
            word_index++;
        }

        if ((!letter && word_index > 0u) || i == end_index)
        {
            auto to_upper = !check_if_short_word(word, word_index, short_words);

            write_word(data, start_index, word, word_index, to_upper);
            word_index = 0u;
        }
    }
}

} // namespace text_conversion_constexpr
