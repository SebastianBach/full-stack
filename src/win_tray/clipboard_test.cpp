#include "clipboard.h"
#include "cstdlib"
#include <iostream>
#include <optional>
#include <source_location>

using test_result = std::optional<std::source_location>;

constexpr static test_result test_success = {};

#define EXPECT(TEST)                                                           \
    if ((TEST) == false)                                                       \
        return test_result{std::source_location::current()};

#define TEST(F)                                                                \
    if (const auto res = F(); res.has_value())                                 \
    {                                                                          \
        std::cout << "Error in test: " << res.value().function_name()          \
                  << ", Line: " << res.value().line() << std::endl;            \
        return EXIT_FAILURE;                                                   \
    }

clipboard::text operator"" _text(const wchar_t* str, size_t)
{
    return clipboard::text{str, str + wcslen(str) + 1};
}

test_result test_clipboard_clear()
{
    const clipboard::text input_text = L"abc"_text;

    clipboard::set_text(input_text);

    {
        clipboard::text check;
        clipboard::get_text(check);

        EXPECT(!check.empty());

        EXPECT(check == input_text);
    }

    clipboard::clear();

    {
        clipboard::text check;
        clipboard::get_text(check);

        EXPECT(check.empty());
    }

    return test_success;
}

test_result test_clipboard_format()
{
    const clipboard::text input_text = L"this is a test"_text;
    ;

    clipboard::set_text(input_text);

    {
        clipboard::text check;
        clipboard::get_text(check);

        EXPECT(!check.empty());

        EXPECT(check == input_text);
    }

    clipboard::format_text();

    {
        clipboard::text check;
        clipboard::get_text(check);

        EXPECT(!check.empty());

        const clipboard::text expected = L"This Is a Test"_text;

        EXPECT(check == expected);
    }

    return test_success;
}

int main()
{
    TEST(test_clipboard_clear);

    TEST(test_clipboard_format);

    return EXIT_SUCCESS;
}
