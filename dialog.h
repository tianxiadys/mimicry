#pragma once
#include "control.h"
#include "progress.h"

class Dialog
{
    Control control = {};
    Password password = {};
    Progress progress = {};

public:
    INT_PTR dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            messageCommand((int)wParam & 0xFFFF);
            return 1;
        case WM_INITDIALOG:
            control.messageInit(hDlg);
            password.messageInit(hDlg);
            progress.messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }

    void messageCommand(int itemId)
    {
        switch (itemId)
        {
        case ID_DECRYPT:
            progress.startWork(password, 0);
            break;
        case ID_ENCRYPT:
            progress.startWork(password, 1);
            break;
        case ID_SHOW:
            control.buttonShow();
            break;
        default: ;
        }
    }
};
