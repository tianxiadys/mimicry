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

    int getPassword(PSTR output, int outputSize)
    {
        wchar_t wPassword[48] = {};
        const auto count = GetWindowTextW(hPassword, wPassword, 48);
        if (count < 4)
        {
            getPasswordTips(L"至少填写四位密码", L"密码太短");
            return 0;
        }
        if (count > 40)
        {
            getPasswordTips(L"至多填写四十位密码", L"密码太长");
            return 0;
        }
        WideCharToMultiByte(CP_UTF8, 0, wPassword, -1, output, outputSize, nullptr, nullptr);
        return 1;
    }

    void getPasswordTips(PCWSTR text, PCWSTR title)
    {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM)&info);
    }

    int getSelected(PWSTR output, int outputSize, int isEncrypt)
    {
        wchar_t wCurrent[260] = {};
        GetCurrentDirectoryW(260, wCurrent);
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = output;
        info.nMaxFile = outputSize;
        info.lpstrInitialDir = wCurrent;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!isEncrypt)
        {
            info.lpstrFilter = L"*.1\0*.1\0\0";
        }
        if (!GetOpenFileNameW(&info))
        {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL)
            {
                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
            }
            return 0;
        }
        return 1;
    }
};
