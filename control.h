#pragma once
#include "resource.h"

class Control
{
    HWND hDialog = nullptr;
    HWND hDecrypt = nullptr;
    HWND hEncrypt = nullptr;
    wchar_t wCurrent[260] = {};
    wchar_t wSelected[8000] = {};

public:
    Control()
    {
        GetCurrentDirectoryW(260, wCurrent);
    }

    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
    }

    PCWSTR getSelected(int isEncrypt)
    {
        wmemset(wSelected, 0, 8000);
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = wSelected;
        info.nMaxFile = 8000;
        info.lpstrInitialDir = wCurrent;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!isEncrypt)
        {
            info.lpstrFilter = L"*.1\0*.1\0\0";
        }
        const auto result = GetOpenFileNameW(&info);
        if (!result)
        {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL)
            {
                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
            }
            return nullptr;
        }
        return wSelected;
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hDecrypt, isEnable);
        EnableWindow(hEncrypt, isEnable);
    }
};
