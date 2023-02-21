#pragma once

#include <array>
#include <concepts>
#include <ranges>

namespace text_conversion_constexpr
{
/*
 * Converts the given text to tilte case style.
 *
 * https://apastyle.apa.org/style-grammar-guidelines/capitalization/title-case
 *
 * @param[in,out] data      The text to convert
 */
template <typename DATA>
requires std::ranges::sized_range<DATA>
constexpr void convert_to_title_case(DATA& data)
{
    if (data.empty())
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

    auto comp_str = [](const char* word_a, const auto* d, auto length)
    {
        for (auto i = 0u; i < length; ++i)
            if (word_a[i] != d[i])
                return false;
        return true;
    };

    auto update_word = [&](auto offset)
    {
        if (is_lower(data[offset]))
            make_upper(data[offset]);
    };

    auto check_if_short_word =
        [&](const auto* word, auto word_length, const auto& short_words)
    {
        for (const auto* short_word : short_words)
        {
            const auto len = strlen_constexpr(short_word);
            if (len == word_length)
                if (comp_str(short_word, word, word_length))
                    return true;
        }
        return false;
    };

    const auto short_words = {"a",   "an",  "the", "and", "as", "but",
                              "for", "if",  "nor", "or",  "so", "yet",
                              "at",  "by",  "for", "in",  "of", "off",
                              "on",  "per", "to",  "up",  "via"};

    using data_type = std::ranges::range_value_t<decltype(data)>;

    data_type* word_start  = nullptr;
    auto       word_length = 0u;
    auto       start_index = 0u;

    // first letter
    update_word(0);

    const auto size      = data.size();
    const auto end_index = size - 1u;

    for (auto i = 0u; i < size; ++i)
    {
        const auto letter = is_letter(data[i]);
        if (letter)
        {
            if (word_length == 0u)
            {
                start_index = i;
                word_start  = &data[i];
            }

            word_length++;
        }

        if ((!letter && word_length > 0u) || i == end_index)
        {
            const auto to_upper =
                !check_if_short_word(word_start, word_length, short_words);

            if (to_upper)
                update_word(start_index);
            word_length = 0u;
        }
    }
}

} // namespace text_conversion_constexpr
