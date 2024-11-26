#include "resource.h"

void buttonDecrypt()
{
}

void buttonEncrypt()
{
}

void buttonShowPassword(HWND hDlg)
{
    const auto hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
    const auto isShow = IsDlgButtonChecked(hDlg, ID_D1_SHOW);
    SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
    InvalidateRect(hPassword, nullptr, 1);
}

void messageCommand(HWND hDlg, UINT itemId)
{
    switch (itemId)
    {
    case ID_D1_DECRYPT:
        buttonDecrypt();
        break;
    case ID_D1_ENCRYPT:
        buttonEncrypt();
        break;
    case ID_D1_SHOW:
        buttonShowPassword(hDlg);
        break;
    }
}

INT_PTR CALLBACK dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;
    case WM_COMMAND:
        messageCommand(hDlg, wParam & 0xFFFF);
        break;
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    DialogBoxParamW(nullptr, RC_D1_WND, nullptr, dialogMain, 0);
    return 0;
}
