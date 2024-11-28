#pragma once
#include "resource.h"

class Password
{
    HWND hPassword = nullptr;
    HWND hCheck = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hCheck = GetDlgItem(hDlg, ID_SHOW);
    }

    void buttonShow()
    {
        const auto isShow = SendMessageW(hCheck, BM_GETCHECK, 0, 0);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    int getPassword(PWSTR output, int outputSize)
    {
        const auto realSize = GetWindowTextW(hPassword, output, outputSize);
        if (realSize < 4)
        {
            getPasswordTips(L"密码太短", L"至少填写四位密码");
            return 0;
        }
        if (realSize > 40)
        {
            getPasswordTips(L"密码太长", L"至多填写四十位密码");
            return 0;
        }
        return realSize;
    }

    void getPasswordTips(PCWSTR title, PCWSTR text)
    {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM)&info);
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hPassword, isEnable);
        EnableWindow(hCheck, isEnable);
    }
};
