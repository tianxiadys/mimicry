#pragma once

#include "worker.h"

class Dialog {
    HWND hDialog = nullptr;
    HWND hPassword = nullptr;
    HWND hMask = nullptr;
    HWND hDetails = nullptr;
    HWND hProgress = nullptr;
    HWND hEncrypt = nullptr;
    HWND hDecrypt = nullptr;
    wchar_t *pFileNext = nullptr;
    int bEncrypt = 0;
    int nTotal = 0;
    int nClose = 0;
    int nSuccess = 0;
    int nError = 0;
    char cPassword[144] = {};
    wchar_t wFileList[8000] = {};
    wchar_t wFileName[260] = {};
    wchar_t wMessage[2000] = {};

public:
    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case APP_RESULT:
                taskResult((PCWSTR) lParam);
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

    void messageInit(HWND hDlg) {
        hDialog = hDlg;
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hMask = GetDlgItem(hDlg, ID_MASK);
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
    }

    void messageCommand(int itemId) {
        switch (itemId) {
            case ID_DECRYPT:
                bEncrypt = 0;
                taskStart();
                break;
            case ID_ENCRYPT:
                bEncrypt = 1;
                taskStart();
                break;
            case ID_MASK:
                passwordMask();
                break;
            default:;
        }
    }

    int passwordGet() {
        wchar_t wPassword[48] = {};
        const auto count = GetWindowTextW(hPassword, wPassword, 48);
        if (count < 4) {
            passwordTips(L"至少填写四位密码", L"密码太短");
            return 0;
        }
        if (count > 40) {
            passwordTips(L"至多填写四十位密码", L"密码太长");
            return 0;
        }
        if (!WideCharToMultiByte(CP_UTF8, 0, wPassword, -1, cPassword, 144, nullptr, nullptr)) {
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

    int fileListGet() {
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = wFileList;
        info.nMaxFile = 8000;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!bEncrypt) {
            info.lpstrFilter = L"*.1\0*.1\0\0";
        }
        if (!GetModuleFileNameW(nullptr, wFileList, 260)) {
            return 0;
        }
        if (!PathRemoveFileSpecW(wFileList)) {
            return 0;
        }
        if (!GetOpenFileNameW(&info)) {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL) {
                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
            }
            return 0;
        }
        wFileList[info.nFileOffset - 1] = 0;
        pFileNext = wFileList;
        return 1;
    }

    int fileListTotal() {
        int total = 0;
        for (int i = 0; i < 8000; i++) {
            if (wFileList[i] == 0) {
                if (wFileList[i + 1] == 0) {
                    break;
                }
                total++;
            }
        }
        return total;
    }

    int fileListNext() {
        if (pFileNext != nullptr) {
            pFileNext = wcschr(pFileNext, 0);
            if (pFileNext != nullptr) {
                pFileNext++;
                if (*pFileNext != 0) {
                    PathCombineW(wFileName, wFileList, pFileNext);
                    return 1;
                } else {
                    pFileNext = nullptr;
                }
            }
        }
        return 0;
    }

    void taskStart() {
        if (!passwordGet()) {
            return;
        }
        if (!fileListGet()) {
            return;
        }
        *wMessage = 0;
        nTotal = fileListTotal();
        nClose = 0;
        nSuccess = 0;
        nError = 0;
        for (int i = 0; i < 5; i++) {
            taskNext();
        }
        taskControl();
    }

    void taskResult(PCWSTR error) {
        if (error) {
            nError++;
            wcscat_s(wMessage, error);
        } else {
            nSuccess++;
        }
        nClose++;
        taskNext();
        taskControl();
    }

    void taskNext() {
        if (fileListNext()) {
            const auto worker = new Worker;
            worker->workerStart();
        }
    }

    void taskControl() {
        wchar_t wText[40] = {};
        swprintf_s(wText, L"总数%d - 成功%d - 失败%d", nTotal, nSuccess, nError);
        SetWindowTextW(hDetails, wText);
        SendMessageW(hProgress, PBM_SETPOS, nClose * 100 / nTotal, 0);
        if (nClose >= nTotal) {
            EnableWindow(hDecrypt, 1);
            EnableWindow(hEncrypt, 1);
            EnableWindow(hPassword, 1);
            if (wcslen(wMessage)) {
                MessageBoxW(hDialog, wMessage, L"错误", 0);
            }
        } else {
            EnableWindow(hDecrypt, 0);
            EnableWindow(hEncrypt, 0);
            EnableWindow(hPassword, 0);
        }
    }
};
