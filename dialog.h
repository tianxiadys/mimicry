#pragma once
#include "password.h"

class Dialog
{
    Password password = {};

public:
    int dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            return 1;
        case WM_INITDIALOG:
            password.messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }
};
