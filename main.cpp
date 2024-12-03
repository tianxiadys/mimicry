#include "dialog.h"

static Dialog *dialog = nullptr;

static INT_PTR CALLBACK staticMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    return dialog->messageMain(hDlg, message, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    dialog = new Dialog;
    DialogBoxParamW(nullptr, RC_DIALOG, nullptr, staticMain, 0);
    delete dialog;
    return 0;
}
