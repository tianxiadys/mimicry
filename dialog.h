#pragma once
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
        case APP_NEXT:
            progress.nextWork(control, (int)wParam);
            return 1;
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            if (wParam == ID_DECRYPT || wParam == ID_ENCRYPT)
            {
                const auto isEncrypt = wParam == ID_ENCRYPT;
                progress.startWork(password, 0);
                return 1;
            }
            if (wParam == ID_ENCRYPT)
            {
                progress.startWork(password, 1);
                return 1;
            }
            if (wParam == ID_SHOW)
            {
                control.buttonShow();
                return 1;
            }
            return 0;
        case WM_INITDIALOG:
            control.messageInit(hDlg);
            password.messageInit(hDlg);
            progress.messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }
};
