#include "clipboard.h"
#include "text_conversion_constexpr.h"
#include <vector>
#include <windows.h>

namespace clipboard
{

using text = std::vector<wchar_t>;

static void get_text(text& text)
{
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
        return;

    if (!OpenClipboard(nullptr))
        return;

    auto hData = GetClipboardData(CF_UNICODETEXT);

    if (hData != nullptr)
    {
        auto* clipboard_text = static_cast<wchar_t*>(GlobalLock(hData));

        if (clipboard_text != nullptr)
        {
            auto textLen = wcslen(clipboard_text);

            text.resize(textLen + 1);

            memcpy(text.data(), clipboard_text, textLen * sizeof(wchar_t));

            text[textLen] = L'\0';

            GlobalUnlock(hData);
        }
    }

    CloseClipboard();
}

static void set_text(const text& text)
{
    if (!OpenClipboard(nullptr))
        return;

    EmptyClipboard();

    const auto len = text.size();

    auto hGlob = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(wchar_t));

    if (hGlob != nullptr)
    {
        void* pGlob = GlobalLock(hGlob);

        if (pGlob)
            memcpy(pGlob, text.data(), len * sizeof(wchar_t));

        GlobalUnlock(hGlob);

        SetClipboardData(CF_UNICODETEXT, hGlob);
    }

    CloseClipboard();
}

void clear()
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        CloseClipboard();
    }
}

void format_text()
{
    std::vector<wchar_t> text;

    get_text(text);

    if (text.empty())
        return;

    text_conversion_constexpr::convert_to_title_case(text);

    set_text(text);
}

} // namespace clipboard
