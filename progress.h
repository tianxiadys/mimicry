#pragma once
#include "password.h"
#include "worker.h"

class Progress
{
    wchar_t wMessage[2000] = {};

public:
    void messageInit(HWND hDlg)
    {
    }

    void startWork(Password& password, int isEncrypt)
    {
    }

    void addResult(int result, PCWSTR wError)
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
};
