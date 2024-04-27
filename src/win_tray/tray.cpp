#include <windows.h>
// windows.h must be the first include

#include "clipboard.h"
#include "resources.h"
#include <shellapi.h>

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

void close()
{
    Shell_NotifyIcon(NIM_DELETE, &nid);
    PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
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
        close();
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ACTIONS::CONVERT_CLIPBOARD:
            clipboard::format_text();
            break;
        case ACTIONS::CLEAR_CLIPBOARD:
            clipboard::clear();
            MessageBox(hwnd, "Clipboard Cleared", "Info", MB_OK);
            break;
        case ACTIONS::EXIT:
            close();
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
    strcpy_s(nid.szTip, "Title Case Conversion");
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
