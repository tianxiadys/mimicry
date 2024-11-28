#pragma once
#include "resource.h"
#include "worker.h"

class Progress
{
    HWND hDialog = nullptr;
    HWND hDetails = nullptr;
    HWND hProgress = nullptr;
    wchar_t wMessage[2000] = {};
    PCWSTR pDirectory = nullptr;
    PCWSTR pCurrent = nullptr;

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

    void startWork(PCSTR cPassword, PCWSTR wSelected, int isEncrypt)
    {
        wmemset(wMessage, 0, 2000);
        pDirectory = wSelected;
        pCurrent = nullptr;
    }

    void addResult(PCWSTR wError)
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
    //
    // wchar_t* getNextFile()
    // {
    //     if (fileNext == nullptr)
    //     {
    //         fileNext = fileBuffer;
    //         fileIndex = 0;
    //     }
    //     fileNext = wcschr(fileNext, 0);
    //     if (fileNext != nullptr)
    //     {
    //         fileIndex++;
    //         fileNext++;
    //         if (*fileNext == 0)
    //         {
    //             fileNext = nullptr;
    //         }
    //     }
    //     return fileNext;
    // }
    //
    // void resetWorker()
    // {
    //     wmemset(fileBuffer, 0, 4096);
    //     fileNext = nullptr;
    //     fileIndex = 0;
    //     fileTotal = 0;
    // }
};
