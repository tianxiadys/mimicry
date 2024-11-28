#pragma once
#include "resource.h"

class Worker
{
    HWND hDialog = nullptr;
    wchar_t* fileNext = nullptr;
    int fileIndex = 0;
    int fileTotal = 0;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
    }

    void startWorker(PCWSTR passwordW, PCWSTR fileListW, int isEncrypt)
    {
    }

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
