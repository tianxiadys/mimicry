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

    void messageEnable(int bEnable)
    {
        EnableWindow(hPassword, bEnable);
        EnableWindow(hCheck, bEnable);
    }

    void buttonShow()
    {
        const auto isShow = SendMessageW(hCheck, BM_GETCHECK, 0, 0);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    int getPassword(PSTR passwordC, int maxC)
    {
        wchar_t passwordW[50];
        const auto sizeW = GetWindowTextW(hPassword, passwordW, 50);
        if (sizeW < 4)
        {
            getPasswordTips(L"密码太短", L"至少填写四位密码");
            return 0;
        }
        if (sizeW > 40)
        {
            getPasswordTips(L"密码太长", L"至多填写四十位密码");
            return 0;
        }
        return WideCharToMultiByte(CP_UTF8, 0, passwordW, sizeW, passwordC, maxC, nullptr, nullptr);
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
};
