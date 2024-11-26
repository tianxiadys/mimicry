#include "dialog.h"

static Dialog* masterDlg = nullptr;

static INT_PTR CALLBACK staticMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return masterDlg->dialogMain(hDlg, message, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    masterDlg = new Dialog;
    DialogBoxParamW(nullptr, RC_D1_WND, nullptr, staticMain, 0);
    delete masterDlg;
    return 0;
}
