#pragma once
#include "resource.h"

class Progress
{
    HWND hDetails = nullptr;
    HWND hProgress = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
    }

    void setProgress(int total, int running, int done)
    {
        wchar_t buffer[30];
        swprintf_s(buffer, L"总数%d - 进行中%d - 完成%d", total, running, done);
        SetWindowTextW(hDetails, buffer);
        SendMessageW(hProgress, PBM_SETPOS, done * 100 / total, 0);
    }
};
