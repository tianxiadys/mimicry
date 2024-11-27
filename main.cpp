#include "dialog.h"

static Dialog* dialog1 = nullptr;

static INT_PTR CALLBACK dialogMain1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return dialog1->dialogMain(hDlg, message, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    dialog1 = new Dialog;
    DialogBoxParamW(nullptr, RC_DIALOG, nullptr, dialogMain1, 0);
    delete dialog1;
    return 0;
}
