#pragma once

#include "resource.h"

class Password {
    char cPassword[144] = {};

public:
    void dialogInit(HWND hDlg) {

    }

    int passwordGet(HWND hDialog) {
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

    void passwordMask(HWND hDialog) {
        const auto bMask = SendMessageW(hMask, BM_GETCHECK, 0, 0);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, bMask ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    void passwordTips(HWND hDialog, PCWSTR text, PCWSTR title) {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendDlgItemMessageW(hDialog, ID_PASSWORD, EM_SHOWBALLOONTIP, 0, (LPARAM) &info);
    }
};
