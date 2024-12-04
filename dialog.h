#pragma once

#include "OpenFileDialog.h"
#include "worker.h"

class Dialog {
    OpenFileDialog openFileDialog = {};
    HWND hDialog = nullptr;
    HWND hPassword = nullptr;
    HWND hMask = nullptr;
    HWND hDetails = nullptr;
    HWND hProgress = nullptr;
    HWND hEncrypt = nullptr;
    HWND hDecrypt = nullptr;
    int bEncrypt = 0;
    int nTotal = 0;
    int nClose = 0;
    int nSuccess = 0;
    int nError = 0;
    wchar_t wMessage[2000] = {};

public:
    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case APP_RESULT:
                //taskResult((PCWSTR) lParam);
                return 1;
            case WM_CLOSE:
                EndDialog(hDlg, 0);
                return 1;
            case WM_COMMAND:
                messageCommand((int) wParam);
                return 1;
            case WM_INITDIALOG:
                messageInit(hDlg);
                return 1;
            default:
                return 0;
        }
    }

    void messageCommand(int itemId) {
        switch (itemId) {
            case ID_DECRYPT:
                //bEncrypt = 0;
                //taskStart();
                break;
            case ID_ENCRYPT:
                openFileDialog.openFile(hDialog, 1);
                //bEncrypt = 1;
                //taskStart();
                break;
            case ID_MASK:
                //passwordMask();
                break;
            default:;
        }
    }

    void messageInit(HWND hDlg) {
        hDialog = hDlg;
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hMask = GetDlgItem(hDlg, ID_MASK);
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
    }


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
//
//    void taskControl() {
//        taskProgress();
//        taskEnable();
//        taskMessage();
//    }
//
//    void taskProgress() {
//        wchar_t wText[40] = {};
//        swprintf_s(wText, L"总数%d - 成功%d - 失败%d", nTotal, nSuccess, nError);
//        SetWindowTextW(hDetails, wText);
//        SendMessageW(hProgress, PBM_SETPOS, nClose * 100 / nTotal, 0);
//    }
//
//    void taskEnable() {
//        const auto bEnable = nClose >= nTotal;
//        EnableWindow(hDecrypt, bEnable);
//        EnableWindow(hEncrypt, bEnable);
//        EnableWindow(hPassword, bEnable);
//    }
//
//    void taskMessage() {
//        if (nClose >= nTotal) {
//            if (wcslen(wMessage)) {
//                MessageBoxW(hDialog, wMessage, L"错误", 0);
//            }
//        }
//    }
};
