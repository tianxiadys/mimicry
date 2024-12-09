#pragma once

#include "dialogDetails.h"
#include "dialogExplorer.h"
#include "dialogPassword.h"
#include "worker.h"

class Dialog {
    DialogDetails details = {};
    DialogExplorer explorer = {};
    DialogPassword password = {};

    void dialogSetIcon(HWND hDlg) {
        const auto hInst = GetModuleHandleW(nullptr);
        const auto hIcon = LoadIconW(hInst, RC_ICON);
        SendMessageW(hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        SendMessageW(hDlg, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
    }

public:
    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_CLOSE:
                EndDialog(hDlg, 0);
                return 1;
            case WM_COMMAND:
                password.messageCommand(wParam);
                return 1;
            case WM_INITDIALOG:
                details.messageInit(hDlg);
                explorer.messageInit(hDlg);
                password.messageInit(hDlg);
                dialogSetIcon(hDlg);
                return 1;
            default:
                return 0;
        }
    }

//
//    void taskStart() {
//        if (!passwordGet()) {
//            return;
//        }
//        if (!fileListGet()) {
//            return;
//        }
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
};
