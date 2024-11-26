#include "resource.h"

int inputPassword(HWND hDlg, wchar_t* output, int outputSize)
{
    const auto hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
    const auto realSize = GetDlgItemTextW(hDlg, ID_D1_PASSWORD, output, outputSize);
    if (realSize < 4)
    {
        EDITBALLOONTIP tips = {};
        tips.cbStruct = sizeof(EDITBALLOONTIP);
        tips.pszTitle = L"密码太短";
        tips.pszText = L"必须填写至少四位密码";
        tips.ttiIcon = TTI_ERROR;
        Edit_ShowBalloonTip(hPassword, &tips);
        return 0;
    }
    return 1;
}

void buttonDecrypt(HWND hDlg)
{
    wchar_t passwordW[50];
    const auto lengthW = inputPassword(hDlg, passwordW, 50);
}

void buttonEncrypt(HWND hDlg)
{
    wchar_t passwordW[50];
    const auto lengthW = inputPassword(hDlg, passwordW, 50);
}

void buttonShow(HWND hDlg)
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
        buttonDecrypt(hDlg);
        break;
    case ID_D1_ENCRYPT:
        buttonEncrypt(hDlg);
        break;
    case ID_D1_SHOW:
        buttonShow(hDlg);
        break;
    default:
        break;
    }
}

INT_PTR CALLBACK dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return 1;
    case WM_COMMAND:
        messageCommand(hDlg, wParam & 0xFFFF);
        return 1;
    default:
        return 0;
    }
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    DialogBoxParamW(nullptr, RC_D1_WND, nullptr, dialogMain, 0);
    return 0;
}
