#pragma once

#include "dialogDetails.h"
#include "dialogPassword.h"
#include "worker.h"

class Dialog {
public:
    DialogDetails details = {};
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
                password.messageInit(hDlg);
                return 1;
            default:
                return 0;
        }
    }

//    int fileListGet(PWSTR output, int outputSize, int bEncrypt) {
//        OPENFILENAMEW info = {};
//        info.lStructSize = sizeof(OPENFILENAMEW);
//        info.hwndOwner = hDialog;
//        info.lpstrFile = output;
//        info.nMaxFile = outputSize;
//        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
//        if (!bEncrypt) {
//            info.lpstrFilter = L"*.1\0*.1\0\0";
//        }
//        if (!GetModuleFileNameW(nullptr, output, 260)) {
//            return 0;
//        }
//        if (!PathRemoveFileSpecW(output)) {
//            return 0;
//        }
//        if (!GetOpenFileNameW(&info)) {
//            const auto reason = CommDlgExtendedError();
//            if (reason == FNERR_BUFFERTOOSMALL) {
//                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
//            }
//            return 0;
//        }
//        output[info.nFileOffset - 1] = 0;
//        return 1;
//    }
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
