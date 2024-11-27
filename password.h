#pragma once
#include "resource.h"

class Password
{
    HWND hDialog = nullptr;
    HWND hPassword = nullptr;
    wchar_t passwordW[50] = {};
    char passwordB[150] = {};

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
    }

    void messageCommand(UINT itemId)
    {
        switch (itemId)
        {
        case ID_DECRYPT:
            inputPassword();
            break;
        case ID_ENCRYPT:
            inputPassword();
            break;
        case ID_SECRET:
            buttonSecret();
            break;
        default:
            break;
        }
    }

    void buttonSecret()
    {
        const auto isShow = IsDlgButtonChecked(hDialog, ID_SECRET);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    int inputPassword()
    {
        int length = inputPasswordLength();
        if (length > 0)
        {
            length = GetWindowTextW(hPassword, passwordW, 50);
            length = WideCharToMultiByte(CP_UTF8, 0, passwordW, length, passwordB, 150, nullptr, nullptr);
        }
        return length;
    }

    int inputPasswordLength()
    {
        const auto length = GetWindowTextLengthW(hPassword);
        if (length < 4)
        {
            inputPasswordTips(L"密码太短", L"至少填写四位密码");
            return 0;
        }
        if (length > 40)
        {
            inputPasswordTips(L"密码太长", L"至多填写四十位密码");
            return 0;
        }
        return length;
    }

    void inputPasswordTips(PCWSTR title, PCWSTR text)
    {
        EDITBALLOONTIP tips = {};
        tips.cbStruct = sizeof(EDITBALLOONTIP);
        tips.pszTitle = title;
        tips.pszText = text;
        tips.ttiIcon = TTI_ERROR;
        Edit_ShowBalloonTip(hPassword, &tips);
    }
};
