#pragma once
#include "control.h"
#include "password.h"
#include "progress.h"

class Dialog
{
    Control control = {};
    Password password = {};
    Progress progress = {};
    wchar_t passwordW[48] = {};
    wchar_t selectedW[8000] = {};

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
            control.messageInit(hDlg);
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
        wmemset(passwordW, 0, 48);
        wmemset(selectedW, 0, 8000);
        if (!password.getPassword(passwordW, 48))
        {
            return;
        }
        if (!control.getFileList(selectedW, 8000, isEncrypt))
        {
            return;
        }
    }
};
