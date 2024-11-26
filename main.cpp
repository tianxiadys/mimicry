#include "resource.h"

void buttonShowPassword(HWND hWnd)
{
    const auto hPassword = GetDlgItem(hWnd, ID_D1_PASSWORD);
    const auto isShow = IsDlgButtonChecked(hWnd, ID_D1_SHOW);
    SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
    InvalidateRect(hPassword, nullptr, 1);
}

void messageCommand(HWND hWnd, UINT srcId)
{
    switch (srcId)
    {
    case ID_D1_SHOW:
        buttonShowPassword(hWnd);
        break;
    }
}

INT_PTR CALLBACK dialogMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        break;
    case WM_COMMAND:
        messageCommand(hWnd, wParam & 0xFFFF);
        break;
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    DialogBoxParamW(nullptr, RC_D1_WND, nullptr, dialogMain, 0);
    return 0;
}
