#pragma once

#include "resource.h"

class DialogPassword {
    HWND hMask = nullptr;
    HWND hPassword = nullptr;
    WCHAR wPassword[48] = {};
    CHAR cPassword[144] = {};

    void passwordTips(PCWSTR text, PCWSTR title) {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM) &info);
    }

public:
    void messageInit(HWND hDlg) {
        hMask = GetDlgItem(hDlg, ID_MASK);
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
    }

    void messageCommand(WPARAM wParam) {
        if (wParam == ID_MASK) {
            const auto bMask = SendMessageW(hMask, BM_GETCHECK, 0, 0);
            SendMessageW(hPassword, EM_SETPASSWORDCHAR, bMask ? 0 : 0x25CF, 0);
            InvalidateRect(hPassword, nullptr, 1);
        }
    }

    int openPassword() {
        const auto wSize = GetWindowTextW(hPassword, wPassword, 48);
        if (wSize < 4) {
            passwordTips(L"至少填写四位密码", L"密码太短");
            return 0;
        }
        if (wSize > 40) {
            passwordTips(L"至多填写四十位密码", L"密码太长");
            return 0;
        }
        if (!WideCharToMultiByte(CP_UTF8, 0, wPassword, -1, cPassword, 144, nullptr, nullptr)) {
            return 0;
        }
        return 1;
    }

    PCSTR getKey() {
        return cPassword;
    }
};
