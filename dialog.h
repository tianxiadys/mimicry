#pragma once

#include "dialogDetails.h"
#include "dialogExplorer.h"
#include "dialogPassword.h"
#include "workerMaster.h"

class Dialog {
    DialogDetails details = {};
    DialogExplorer explorer = {};
    DialogPassword password = {};
    WorkerMaster master = {};

    void messageInit(HWND hDlg) {
        initIcon(hDlg);
    }

    void messageCommand(WPARAM wParam) {
        switch (wParam) {
            case ID_CLEAR:
                commandClear();
                break;
            case ID_DECRYPT:
            case ID_ENCRYPT:
                commandEncrypt(wParam);
                break;
            default:;
        }
    }

    void initIcon(HWND hDlg) {
        const auto hInst = GetModuleHandleW(nullptr);
        const auto hIcon = LoadIconW(hInst, RC_ICON);
        SendMessageW(hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        SendMessageW(hDlg, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
    }

    void commandClear() {
        while (const auto runner = master.removeFinish()) {
            details.removeItem(runner->index);
            delete runner;
        }
    }

    void commandEncrypt(WPARAM wParam) {
        if (!password.openPassword()) {
            return;
        }
        if (!explorer.openExplorer()) {
            return;
        }
        const auto key = password.getPassword();

        //        if (const auto key = password.getPassword()) {
        //            if (explorer.openExplorer(bEncrypt)) {
        //                while (const auto next = explorer.getNext()) {
        //                    const auto worker = new CoreRC4;
        //                    worker->workerStart(hDialog, key, next, bEncrypt);
        //                }
        //            }
        //        }
        //
        //    void taskStart() {
        //        *wMessage = 0;
        //        nTotal = fileListTotal();
        //        nClose = 0;
        //        nSuccess = 0;
        //        nError = 0;
        //        for (int i = 0; i < 5; i++) {
        //            taskNext();
        //        }
        //        taskControl();
        //    }
        //
        //    void taskResult(PCWSTR error) {
        //        if (error) {
        //            nError++;
        //            wcscat_s(wMessage, error);
        //        } else {
        //            nSuccess++;
        //        }
        //        nClose++;
        //        taskNext();
        //        taskControl();
        //    }
        //
        //    void taskNext() {
        //        if (fileListNext()) {
        //            const auto worker = new Worker;
        //            worker->workerStart();
        //        }
        //    }
    }

public:
    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_CLOSE:
                EndDialog(hDlg, 0);
                return 1;
            case WM_COMMAND:
                password.messageCommand(wParam);
                messageCommand(wParam);
                return 1;
            case WM_INITDIALOG:
                details.messageInit(hDlg);
                explorer.messageInit(hDlg);
                password.messageInit(hDlg);
                messageInit(hDlg);
                return 1;
            default:
                return 0;
        }
    }
};
