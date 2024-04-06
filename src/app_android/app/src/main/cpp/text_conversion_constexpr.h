#pragma once
#include <array>

namespace text_conversion_constexpr
{
    inline const char* version()
    {
        return "0.1.2";
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
    } // namespace intern

/*
 * Converts the given text to title case style.
 *
 * https://apastyle.apa.org/style-grammar-guidelines/capitalization/title-case
 *
 * @param[in,out] data      The text to convert
 */
    template <typename DATA>
    constexpr void convert_to_title_case(DATA& data)
    {
        if (data.empty())
            return;

        auto is_letter = [&](const auto& letter)
        {
            return (letter >= 65 && letter <= 90) ||
                   (letter >= 97 && letter <= 122) || letter == 39;
        };

        auto comp_str = [](const char* word_a, const auto* d, auto length)
        {
            for (auto i = 0u; i < length; ++i)
                if (word_a[i] != d[i])
                    return false;
            return true;
        };

        auto make_upper_case = [&](auto offset)
        {
            auto& letter = data[offset];
            // check if lower case letter
            if (letter >= 97 && letter <= 122)
                letter -= 32;
        };

        auto check_if_short_word =
                [&](const auto* word, auto word_length, const auto& short_words)
                {
                    if (word_length >= 4)
                        return false;

                    for (const auto& short_word : short_words)
                        if (short_word.length == word_length)
                            if (comp_str(short_word.word, word, word_length))
                                return true;

                    return false;
                };

        const std::array<intern::short_word, 23> short_words{
                "a",   "an",  "the", "and", "as", "but", "for", "if",
                "nor", "or",  "so",  "yet", "at", "by",  "for", "in",
                "of",  "off", "on",  "per", "to", "up",  "via"};

        auto word_length = 0u;
        auto start_index = 0u;

        // first letter
        make_upper_case(0);

        const auto size = data.size();

        for (auto i = 0u; i < size; ++i)
        {
            const auto letter = is_letter(data[i]);
            if (letter)
            {
                if (word_length == 0u)
                    start_index = i;

                word_length++;
            }

            if ((!letter && word_length > 0u) || i == size - 1u)
            {
                const auto to_upper = !check_if_short_word(
                        &data[start_index], word_length, short_words);

                if (to_upper)
                    make_upper_case(start_index);

                word_length = 0u;
            }
        }
    }

} // namespace text_conversion_constexpr
