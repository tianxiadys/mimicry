#include "resource.h"
#include "password.h"

static Password* password = nullptr;

INT_PTR CALLBACK dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return 1;
    case WM_COMMAND:
        switch (message & 0xFFFF)
        {
        case ID_D1_DECRYPT:
            //buttonDecrypt(hDlg);
            break;
        case ID_D1_ENCRYPT:
            //buttonEncrypt(hDlg);
            break;
        case ID_D1_SHOW:
            password->buttonShow();
            break;
        default:
            break;
        }
        return 1;
    case WM_DESTROY:
        delete password;
        return 1;
    case WM_INITDIALOG:
        password = new Password(hDlg);
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
