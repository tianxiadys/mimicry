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
            password.setEnable((int)wParam);
            return 1;
        case AM_RESULT:
            progress.addResult((PCWSTR)lParam);
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
            buttonEncrypt(0);
            break;
        case ID_ENCRYPT:
            buttonEncrypt(1);
            break;
        case ID_SHOW:
            password.buttonShow();
            break;
        default: ;
        }
    }

    void buttonEncrypt(int isEncrypt)
    {
        const auto passwordW = password.getPassword();
        if (!passwordW)
        {
            return;
        }
        const auto selectedW = control.getSelected(isEncrypt);
        if (!selectedW)
        {
            return;
        }
        progress.startWork(passwordW, selectedW, isEncrypt);
    }
};
