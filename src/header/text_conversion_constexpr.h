#pragma once

#ifdef __cpp_lib_ranges
#ifdef __cpp_lib_concepts
#include <concepts>
#include <ranges>
#define USE_RANGES
#endif
#endif

#include <array>
#include <string>

namespace text_conversion_constexpr
{
inline const char* version()
{
    return "0.1.3";
}

namespace intern
{
struct short_word
{
    template <auto N>
    constexpr short_word(const char (&input)[N]) : word(input), length(N - 1)
    {
    }

    const char*        word;
    const unsigned int length;
};

constexpr auto is_alpha(auto c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

constexpr auto is_lower(auto c)
{
    return (c >= 'a' && c <= 'z');
}

constexpr static auto uppercase = 'a' - 'A';

} // namespace intern

/*
 * Converts the given text to title case style.
 *
 * https://apastyle.apa.org/style-grammar-guidelines/capitalization/title-case
 *
 * @param[in,out] data      The text to convert.
 */
template <typename DATA>
#ifdef USE_RANGES
    requires std::ranges::sized_range<DATA>
#endif
constexpr void convert_to_title_case(DATA& data)
{
    if (data.empty())
        return;

    auto is_letter = [&](const auto& letter)
    {
        return intern::is_alpha(letter) || letter == '\'';
    };

    auto make_upper_case = [&](auto offset)
    {
        auto& letter = data[offset];
        // check if lower case letter
        if (intern::is_lower(letter))
            letter -= intern::uppercase;
    };

    auto check_if_short_word = [&](const auto& word, const auto& short_words)
    {
        if (word.size() >= 4)
            return false;

        for (const auto& short_word : short_words)
            if (short_word == word)
                return true;

        return false;
    };

    const std::array<std::string_view, 22> short_words{
        "a",   "an", "the", "and", "as", "but", "for", "if",
        "nor", "or", "so",  "yet", "at", "by",  "in",  "of",
        "off", "on", "per", "to",  "up", "via"};

    auto word_length = 0u;
    auto start_index = 0u;

    // first letter
    make_upper_case(0);

    const auto size            = data.size();
    const auto last_letter_idx = size - 1u;

    auto first_word = true;

    for (auto i = 0u; i < size; ++i)
    {
        const auto letter = is_letter(data[i]);
        if (letter)
        {
            if (word_length == 0u)
                start_index = i;

            word_length++;
        }

        if ((!letter && word_length > 0u) || i == last_letter_idx)
        {
            const std::string_view word(&data[start_index], word_length);

            const auto to_upper = !check_if_short_word(word, short_words);

            if (to_upper || first_word)
                make_upper_case(start_index);

            word_length = 0u;
            first_word = false;
        }
    }
}

} // namespace text_conversion_constexpr
