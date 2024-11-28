#pragma once
#include "resource.h"

class Control
{
    HWND hDialog = nullptr;
    HWND hDecrypt = nullptr;
    HWND hEncrypt = nullptr;
    wchar_t currentW[260] = {};
    wchar_t selectedW[8000] = {};

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
    }

    PCWSTR getSelected(int isEncrypt)
    {
        wmemset(selectedW, 0, 8000);
        GetCurrentDirectoryW(260, currentW);
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = selectedW;
        info.nMaxFile = 8000;
        info.lpstrInitialDir = currentW;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!isEncrypt)
        {
            info.lpstrFilter = L".1\0*.1\0\0";
        }
        const auto result = GetOpenFileNameW(&info);
        if (result)
        {
            return selectedW;
        }
        const auto reason = CommDlgExtendedError();
        if (reason == FNERR_BUFFERTOOSMALL)
        {
            MessageBoxW(hDialog, L"选择的文件数量超过限制，请分批次处理", L"错误", 0);
        }
        return nullptr;
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hDecrypt, isEnable);
        EnableWindow(hEncrypt, isEnable);
    }
};
