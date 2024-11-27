#pragma once
#include "password.h"
#include "progress.h"

class Dialog
{
    Password password = {};
    Progress progress = {};
    int index = 0;

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
            if (wParam == ID_ENCRYPT)
            {
                progress.setProgress1(index++, 50);
            }
            if (wParam == ID_DECRYPT)
            {
                index = 0;
                progress.setProgress1(index, 50);
            }
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
