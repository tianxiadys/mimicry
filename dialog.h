#pragma once
#include "control.h"
#include "password.h"
#include "progress.h"

class Dialog
{
    Control control = {};
    Password password = {};
    Progress progress = {};

public:
    int dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case AM_ENABLE:
            control.setEnable((int)wParam);
            return 1;
        case AM_RESULT:
            progress.addResult((int)wParam, (PCWSTR)lParam);
            return 1;
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            messageCommand(wParam);
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

    void messageCommand(WPARAM wParam)
    {
        switch (wParam & 0xFFFF)
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
