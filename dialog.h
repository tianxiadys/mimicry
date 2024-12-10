#pragma once

#include "dialogDetails.h"
#include "dialogExplorer.h"
#include "dialogPassword.h"
#include "dialogWorker.h"

class Dialog {
    DialogDetails details = {};
    DialogExplorer explorer = {};
    DialogPassword password = {};
    HWND hDialog = nullptr;

    void messageInit(HWND hDlg) {
        hDialog = hDlg;
        initIcon();
    }

    void messageCommand(WPARAM wParam) {
        switch (wParam) {
            case ID_CLEAR:
                commandClear();
                break;
            case ID_DECRYPT:
                commandEncrypt(0);
                break;
            case ID_ENCRYPT:
                commandEncrypt(1);
                break;
            default:;
        }
    }

    void initIcon() {
        const auto hInst = GetModuleHandleW(nullptr);
        const auto hIcon = LoadIconW(hInst, RC_ICON);
        SendMessageW(hDialog, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        SendMessageW(hDialog, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
    }

    void commandClear() {
    }

    void commandEncrypt(int bEncrypt) {
        const auto worker = new DialogWorker;
        worker->workerInit();
        delete worker;
        //        if (const auto key = password.getPassword()) {
        //            if (explorer.openFile(bEncrypt)) {
        //                while (const auto next = explorer.getNext()) {
        //                    const auto worker = new DialogWorker;
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
