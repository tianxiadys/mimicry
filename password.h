#pragma once
#include "resource.h"

class Password
{
    HWND hPassword = nullptr;
    HWND hCheck = nullptr;
    wchar_t wPassword[48] = {};
    char cPassword[144] = {};

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

    PCSTR getPassword()
    {
        const auto count = GetWindowTextW(hPassword, wPassword, 48);
        if (count < 4)
        {
            showTips(L"密码太短", L"至少填写四位密码");
            return nullptr;
        }
        if (count > 40)
        {
            showTips(L"密码太长", L"至多填写四十位密码");
            return nullptr;
        }
        WideCharToMultiByte(CP_UTF8, 0, wPassword, -1, cPassword, 144, nullptr, nullptr);
        return cPassword;
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hPassword, isEnable);
    }

    void showTips(PCWSTR title, PCWSTR text)
    {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM)&info);
    }
};
