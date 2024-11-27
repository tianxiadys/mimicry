#pragma once
#include "password.h"
#include "progress.h"

class Dialog
{
    Password password = {};
    Progress progress = {};

public:
    int dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            password.messageCommand(wParam & 0xFFFF);
            return 1;
        case WM_INITDIALOG:
            password.messageInit(hDlg);
            progress.messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }
};
