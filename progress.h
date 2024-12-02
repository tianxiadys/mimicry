#pragma once
#include "password.h"

class Progress
{
    HWND hDialog = nullptr;
    char cPassword[144] = {};
    wchar_t wSelected[8000] = {};

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
    }

    void startWork(Password& password, int isEncrypt)
    {
        wmemset(wSelected, 0, 8000);
        if (!password.getPassword(cPassword, 144))
        {
            return;
        }
        if (!password.getSelected(wSelected, 8000, isEncrypt))
        {
            return;
        }
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
};
