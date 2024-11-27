#include "dialog1.h"

static Dialog1* dialog1 = nullptr;

static INT_PTR CALLBACK dialogMain1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return dialog1->dialogMain(hDlg, message, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    dialog1 = new Dialog1;
    DialogBoxParamW(nullptr, RC_DIALOG1, nullptr, dialogMain1, 0);
    delete dialog1;
    return 0;
}
