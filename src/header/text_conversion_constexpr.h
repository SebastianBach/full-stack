#pragma once

#include <array>
#include <concepts>
#include <cstring>
#include <ranges>

namespace text_conversion_constexpr
{
// See
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
    auto make_upper   = [](auto& letter) { letter -= 32; };
    auto make_lower   = [](auto& letter) { letter += 32; };
    auto is_space     = [](const auto& letter) { return letter == 32; };
    auto is_hyphen    = [](const auto& letter) { return letter == 45; };
    auto is_separator = [&](const auto& letter)
    { return is_space(letter) || is_hyphen(letter); };

    auto strlen_constexpr = [](const char* word)
    {
        auto len = 0;
        while (*word != '\0')
        {
            word = word + 1;
            len++;
        }
        return len;
    };

    auto comp_str = [](const char* word_a, auto& d, auto length)
    {
        for (auto i = 0; i < length; ++i)
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
            auto len = strlen_constexpr(short_word);
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
    auto                     word_index  = 0;
    auto                     start_index = 0;

    // first letter
    if (is_lower(data[0]))
        make_upper(data[0]);

    const auto end_index      = size - 1;
    auto       prev_separator = false;

    for (auto i = 0; i < size; ++i)
    {
        const auto letter = is_letter(data[i]);
        if (letter)
        {
            if (word_index == 0)
                start_index = i;

            word[word_index] = data[i];
            word_index++;
        }

        if ((!letter && word_index > 0) || i == end_index)
        {
            auto to_upper = !check_if_short_word(word, word_index, short_words);

            write_word(data, start_index, word, word_index, to_upper);
            word_index = 0;
        }
    }
}

} // namespace text_conversion_constexpr
