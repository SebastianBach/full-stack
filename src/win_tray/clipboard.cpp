#include "clipboard.h"
#include "text_conversion_constexpr.h"
#include <optional>
#include <vector>
#include <windows.h>

namespace
{
namespace intern
{
class clipboard
{
public:
    static std::optional<clipboard> open_clipboard()
    {
        auto open = OpenClipboard(nullptr);
        if (!open)
            return std::nullopt;

        return std::optional<clipboard>{std::in_place};
    }
    clipboard() {}

    ~clipboard()
    {
        CloseClipboard();
    }
};

template <typename HANDLE, auto CLOSE> class free_resource
{
public:
    free_resource(HANDLE handle) : h(handle) {}

    void release()
    {
        h = nullptr;
    }

    ~free_resource()
    {
        if (h)
            CLOSE(h);
    }

    HANDLE h;
};

} // namespace intern
} // namespace

namespace clipboard
{
void get_text(text& text)
{
    if (!IsClipboardFormatAvailable(CF_TEXT))
        return;

    auto clipboard = intern::clipboard::open_clipboard();
    if (!clipboard.has_value())
        return;

    auto hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
        return;

    auto* clipboard_text = static_cast<char*>(GlobalLock(hData));

    const intern::free_resource<HGLOBAL, GlobalUnlock> lock(hData);

    if (clipboard_text == nullptr)
        return;

    text = clipboard_text;
}

void set_text(const text& text)
{
    auto clipboard = intern::clipboard::open_clipboard();
    if (!clipboard.has_value())
        return;

    EmptyClipboard();

    const auto len = text.size() + 1;

    auto hGlob = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(char));
    if (hGlob == nullptr)
        return;

    auto* pGlob = GlobalLock(hGlob);

    if (pGlob)
    {
        memcpy(pGlob, text.data(), len * sizeof(char));

        GlobalUnlock(hGlob);

        SetClipboardData(CF_TEXT, hGlob);
    }
    else
    {
        GlobalFree(hGlob);
    }
}

void clear()
{
    auto clipboard = intern::clipboard::open_clipboard();
    if (clipboard.has_value())
        EmptyClipboard();
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
