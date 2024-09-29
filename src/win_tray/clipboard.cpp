#include "clipboard.h"
#include "text_conversion_constexpr.h"
#include <vector>
#include <windows.h>

namespace clipboard
{
void get_text(text& text)
{
    if (!IsClipboardFormatAvailable(CF_TEXT))
        return;

    if (!OpenClipboard(nullptr))
        return;

    auto hData = GetClipboardData(CF_TEXT);

    if (hData != nullptr)
    {
        auto* clipboard_text = static_cast<char*>(GlobalLock(hData));

        if (clipboard_text != nullptr)
        {
            auto textLen = strlen(clipboard_text);

            text.resize(textLen + 1);

            memcpy(text.data(), clipboard_text, textLen * sizeof(char));

            text[textLen] = L'\0';

            GlobalUnlock(hData);
        }
    }

    CloseClipboard();
}

void set_text(const text& text)
{
    if (!OpenClipboard(nullptr))
        return;

    EmptyClipboard();

    const auto len = text.size();

    auto hGlob = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(char));

    if (hGlob != nullptr)
    {
        auto* pGlob = GlobalLock(hGlob);

        if (pGlob)
            memcpy(pGlob, text.data(), len * sizeof(char));

        GlobalUnlock(hGlob);

        SetClipboardData(CF_TEXT, hGlob);
    }

    GlobalFree(hGlob);
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
    text text_to_convert;

    get_text(text_to_convert);

    if (text_to_convert.empty())
        return;

    text_conversion_constexpr::convert_to_title_case(text_to_convert);

    set_text(text_to_convert);
}

} // namespace clipboard
