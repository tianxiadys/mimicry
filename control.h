#pragma once
#include "resource.h"

class Control
{
    HWND hDialog = nullptr;
    HWND hDecrypt = nullptr;
    HWND hEncrypt = nullptr;
    wchar_t outputBuffer[8000] = {};
    wchar_t currentDir[260] = {};

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
    }

    PCWSTR getFileList(int isEncrypt)
    {
        wmemset(outputBuffer, 0, 8000);
        GetCurrentDirectoryW(260, currentDir);
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = outputBuffer;
        info.nMaxFile = 8000;
        info.lpstrInitialDir = currentDir;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!isEncrypt)
        {
            info.lpstrFilter = L".1\0*.1\0\0";
        }
        const auto result = GetOpenFileNameW(&info);
        if (result)
        {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL)
            {
                MessageBoxW(hDialog, L"选择的文件数量超过限制，请分批次处理", L"错误", 0);
            }
            return outputBuffer;
        }
        return nullptr;
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hDecrypt, isEnable);
        EnableWindow(hEncrypt, isEnable);
    }
};
