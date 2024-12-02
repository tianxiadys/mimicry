#pragma once
#include "resource.h"

class Control
{
    HWND hCheck = nullptr;
    HWND hDecrypt = nullptr;
    HWND hDetails = nullptr;
    HWND hEncrypt = nullptr;
    HWND hPassword = nullptr;
    HWND hProgress = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hCheck = GetDlgItem(hDlg, ID_SHOW);
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
    }

    void buttonShow()
    {
        const auto isShow = SendMessageW(hCheck, BM_GETCHECK, 0, 0);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hDecrypt, isEnable);
        EnableWindow(hEncrypt, isEnable);
        EnableWindow(hPassword, isEnable);
    }

    void setProgress(int total, int open, int close)
    {
        wchar_t buffer[30];
        swprintf_s(buffer, L"总数%d - 进行中%d - 完成%d", total, open, close);
        SetWindowTextW(hDetails, buffer);
        SendMessageW(hProgress, PBM_SETPOS, close * 100 / total, 0);
    }
};
