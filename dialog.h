#pragma once
#include "control.h"
#include "password.h"

class Dialog
{
    Control control = {};
    Password password = {};
    wchar_t passwordW[48] = {};
    wchar_t fileListW[8000] = {};

public:
    int dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            messageCommand(LOWORD(wParam));
            return 1;
        case WM_INITDIALOG:
            control.messageInit(hDlg);
            password.messageInit(hDlg);
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
            //buttonEncrypt(0);
            break;
        case ID_ENCRYPT:
            //buttonEncrypt(1);
            break;
        case ID_SHOW:
            password.buttonShow();
            break;
        default:
            break;
        }
    }

    //
    // void buttonEncrypt(int isEncrypt)
    // {
    //     if (!password.getPassword(passwordW, 48))
    //     {
    //         return;
    //     }
    //     if (!control.getFileList(fileListW, 8000, isEncrypt))
    //     {
    //         return;
    //     }
    //     control.setEnable(0);
    //     password.setEnable(0);
    //     worker.startWorker(passwordW, fileListW, isEncrypt);
    // }
};
