#include <windows.h>
// windows.h must be the first include

#include "resources.h"
#include "text_conversion_constexpr.h"
#include <shellapi.h>
#include <vector>

enum ACTIONS
{
    CONVERT_CLIPBOARD = 0,
    CLEAR_CLIPBOARD,
    EXIT
};

HINSTANCE      hInst;
NOTIFYICONDATA nid;
HMENU          hPopupMenu;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam);

void create_system_tray_icon(HWND hwnd);

void show_conetxt_menu(HWND hwnd, POINT pt);

void get_clipboard_text(std::vector<wchar_t>& text)
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

void copy_to_clipboard(const std::vector<wchar_t>& text)
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

void edit_clipboard()
{
    std::vector<wchar_t> text;

    get_clipboard_text(text);

    if (text.empty())
        return;

    text_conversion_constexpr::convert_to_title_case(text);

    copy_to_clipboard(text);
}

void clear_clipboard()
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        CloseClipboard();
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    hInst                   = hInstance;
    const char CLASS_NAME[] = "text_conversion_win_tray_class";

    WNDCLASS wc      = {};
    wc.lpfnWndProc   = window_callback;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);
    auto hwnd =
        CreateWindowEx(0, CLASS_NAME, "Sample Tray App", WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
        return 0;

    create_system_tray_icon(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ACTIONS::CONVERT_CLIPBOARD:
            edit_clipboard();
            break;
        case ACTIONS::CLEAR_CLIPBOARD:
            clear_clipboard();
            MessageBox(hwnd, "Clipboard Cleared", "Info", MB_OK);
            break;
        case ACTIONS::EXIT:
            Shell_NotifyIcon(NIM_DELETE, &nid);
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_APP:
        if (lParam == WM_RBUTTONUP)
        {
            POINT pt;
            GetCursorPos(&pt);
            show_conetxt_menu(hwnd, pt);
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void create_system_tray_icon(HWND hwnd)
{
    nid.cbSize           = sizeof(NOTIFYICONDATA);
    nid.hWnd             = hwnd;
    nid.uID              = 1;
    nid.uFlags           = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_APP;
    nid.hIcon            = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON));
    strcpy_s(nid.szTip, "Sample Tray Application");
    Shell_NotifyIcon(NIM_ADD, &nid);
}

void show_conetxt_menu(HWND hwnd, POINT pt)
{
    hPopupMenu = CreatePopupMenu();

    InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING,
               ACTIONS::CONVERT_CLIPBOARD, "Convert Text in Clipboard");

    InsertMenu(hPopupMenu, 1, MF_BYPOSITION | MF_STRING,
               ACTIONS::CLEAR_CLIPBOARD, "Clear Clipboard");

    InsertMenu(hPopupMenu, 2, MF_BYPOSITION | MF_STRING, ACTIONS::EXIT, "Exit");

    SetForegroundWindow(hwnd);

    TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0,
                   hwnd, NULL);
}
