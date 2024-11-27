#pragma once
#include "resource.h"

class Password
{
    HWND hDialog = nullptr;
    HWND hPassword = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
    }

    void messageCommand(UINT itemId)
    {
        if (itemId == ID_SHOW)
        {
            buttonShow();
        }
    }

    void buttonShow()
    {
        const auto isShow = IsDlgButtonChecked(hDialog, ID_SHOW);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    int readPassword(PWSTR passwordW, int maxW)
    {
        const auto sizeW = GetWindowTextW(hPassword, passwordW, maxW);
        if (sizeW < 4)
        {
            readPasswordTips(L"密码太短", L"至少填写四位密码");
            return 0;
        }
        if (sizeW > 40)
        {
            readPasswordTips(L"密码太长", L"至多填写四十位密码");
            return 0;
        }
        return 1;
    }

    void readPasswordTips(PCWSTR title, PCWSTR text)
    {
        EDITBALLOONTIP tips = {};
        tips.cbStruct = sizeof(EDITBALLOONTIP);
        tips.pszTitle = title;
        tips.pszText = text;
        tips.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM)&tips);
    }
};
