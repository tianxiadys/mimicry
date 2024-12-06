#pragma once

#include "dialogDetails.h"
#include "dialogExplorer.h"
#include "dialogPassword.h"
#include "worker.h"

class Dialog {
public:
    DialogDetails details = {};
    DialogExplorer explorer = {};
    DialogPassword password = {};

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
