#pragma once
#include "resource.h"

class Control
{
    HWND hDecrypt = nullptr;
    HWND hEncrypt = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
    }

    void messageEnable(int bEnable)
    {
        EnableWindow(hDecrypt, bEnable);
        EnableWindow(hEncrypt, bEnable);
    }

    void buttonEncrypt(int bEncrypt)
    {
    }
};
