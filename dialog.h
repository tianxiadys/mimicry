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
            messageCommand(wParam, lParam);
            return 1;
        case WM_INITDIALOG:
            password.messageInit(hDlg);
            progress.messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }

    void messageCommand(WPARAM wParam, LPARAM lParam)
    {
        switch (wParam & 0xFFFF)
        {
        case ID_DECRYPT:
            break;
        case ID_ENCRYPT:
            break;
        case ID_SHOW:
            password.buttonShow();
            break;
        default:
            break;
        }
    }
};
