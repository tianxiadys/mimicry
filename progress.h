#pragma once
#include "resource.h"

class Progress
{
    HWND hDialog = nullptr;
    HWND hDetails = nullptr;
    HWND hProgress = nullptr;
    // int nTotal = 0;
    // int nRunning = 0;
    // int nClose = 0;
    // int nSuccess = 0;
    // int nError = 0;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
    }

    void startWork(PCWSTR passwordW, PCWSTR selectedW, int isEncrypt)
    {
    }

    // void setTotal(int total)
    // {
    //     nTotal = total;
    //     nRunning = 0;
    //     nClose = 0;
    //     nSuccess = 0;
    //     nError = 0;
    //     updateProgress();
    // }
    //
    // void updateProgress()
    // {
    //     wchar_t buffer[30];
    //     swprintf_s(buffer, L"总数%d - 进行中%d - 成功%d - 失败%d", nTotal, nRunning, nSuccess, nError);
    //     SetWindowTextW(hDetails, buffer);
    //     SendMessageW(hProgress, PBM_SETPOS, nClose * 100 / nTotal, 0);
    // }
};
