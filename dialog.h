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
            {
                progress.nextWork(control, wParam);
                return 1;
            }
        case WM_CLOSE:
            {
                EndDialog(hDlg, 0);
                return 1;
            }
        case WM_COMMAND:
            {
                switch (wParam)
                {
                case ID_DECRYPT:
                case ID_ENCRYPT:
                    progress.startWork(password, wParam);
                    return 1;
                case ID_SHOW:
                    control.buttonShow();
                    return 1;
                default:
                    return 0;
                }
            }
        case WM_INITDIALOG:
            {
                control.messageInit(hDlg);
                password.messageInit(hDlg);
                progress.messageInit(hDlg);
                return 1;
            }
        default:
            return 0;
        }
    }
};
