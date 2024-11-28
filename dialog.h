#pragma once
#include "worker.h"

class Dialog
{
    Control control = {};
    Password password = {};
    Progress progress = {};
    Worker worker = {};

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

    int getPassword(PWSTR output, int outputSize)
    {
        return password.getPassword(output, outputSize);
    }

    int getFileList(PWSTR output, int outputSize, int isEncrypt)
    {
        return control.getFileList(output, outputSize, isEncrypt);
    }

    void setEnable(int isEnable)
    {
        control.setEnable(isEnable);
        password.setEnable(isEnable);
    }

    void setProgress2(int current1, int total1, int current2, int total2, PCWSTR fileName)
    {
        progress.setProgress1(current1, total1);
        progress.setProgress2(current2, total2, fileName);
    }
};
