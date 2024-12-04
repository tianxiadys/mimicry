#pragma once

#include "worker.h"

class Dialog {
    HWND hDialog = nullptr;
    HWND hPassword = nullptr;
    HWND hMask = nullptr;
    HWND hDetails = nullptr;

public:
    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_CLOSE:
                EndDialog(hDlg, 0);
                return 1;
            case WM_COMMAND:
                messageCommand(LOWORD(wParam));
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
                break;
            case ID_ENCRYPT:
                break;
            case ID_MASK:
                passwordMask();
                break;
            default:;
        }
    }

    void messageInit(HWND hDlg) {
        hDialog = hDlg;
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hMask = GetDlgItem(hDlg, ID_MASK);
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
    }

    void detailsInit() {

    }

    int passwordGet(PSTR output, int outputSize) {
        wchar_t wPassword[48] = {};
        const auto wSize = GetWindowTextW(hPassword, wPassword, 48);
        if (wSize < 4) {
            passwordTips(L"至少填写四位密码", L"密码太短");
            return 0;
        }
        if (wSize > 40) {
            passwordTips(L"至多填写四十位密码", L"密码太长");
            return 0;
        }
        if (!WideCharToMultiByte(CP_UTF8, 0, wPassword, -1, output, outputSize, nullptr, nullptr)) {
            return 0;
        }
        return 1;
    }

    void passwordMask() {
        const auto bMask = SendMessageW(hMask, BM_GETCHECK, 0, 0);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, bMask ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    void passwordTips(PCWSTR text, PCWSTR title) {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM) &info);
    }

    int fileListGet(PWSTR output, int outputSize, int bEncrypt) {
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = output;
        info.nMaxFile = outputSize;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!bEncrypt) {
            info.lpstrFilter = L"*.1\0*.1\0\0";
        }
        if (!GetModuleFileNameW(nullptr, output, 260)) {
            return 0;
        }
        if (!PathRemoveFileSpecW(output)) {
            return 0;
        }
        if (!GetOpenFileNameW(&info)) {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL) {
                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
            }
            return 0;
        }
        output[info.nFileOffset - 1] = 0;
        return 1;
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
