#pragma once
#include "resource.h"

class Control
{
    HWND hDialog = nullptr;
    HWND hDecrypt = nullptr;
    HWND hEncrypt = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
    }

    int getFileList(PWSTR output, int outputSize, int isEncrypt)
    {
        wchar_t currentDir[260] = {};
        GetCurrentDirectoryW(260, currentDir);
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = output;
        info.nMaxFile = outputSize;
        info.lpstrInitialDir = currentDir;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!isEncrypt)
        {
            info.lpstrFilter = L".1\0*.1\0\0";
        }
        return GetOpenFileNameW(&info);
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hDecrypt, isEnable);
        EnableWindow(hEncrypt, isEnable);
    }
};
