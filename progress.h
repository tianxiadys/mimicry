#pragma once
#include "control.h"
#include "password.h"
#include "worker.h"

class Progress
{
    char cPassword[144] = {};
    wchar_t wSelected[8000] = {};
    HWND hDialog = nullptr;
    PCWSTR pNext = nullptr;
    int isEncrypt = 0;
    int nIndex = 0;
    int nTotal = 0;
    int nOpen = 0;
    int nClose = 0;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
    }

    void startWork(Password& password, WPARAM wParam)
    {
        memset(cPassword, 0, 144);
        wmemset(wSelected, 0, 8000);
        pNext = nullptr;
        isEncrypt = wParam == ID_ENCRYPT;
        nIndex = 0;
        nTotal = 0;
        nOpen = 0;
        nClose = 0;
        if (!password.getPassword(cPassword, 144))
        {
            return;
        }
        if (!password.getSelected(wSelected, 8000, isEncrypt))
        {
            return;
        }
        while (nextFile() != nullptr)
        {
            nTotal++;
        }
        SendMessageW(hDialog, APP_NEXT, 0, 0);
    }

    void nextWork(Control& control, WPARAM wParam)
    {
        // if (wParam == 0)
        // {
        //     control.setEnable(0);
        // }
        // for (; nOpen < 5; nOpen++)
        // {
        //     const auto fileName = nextFile();
        //     if (fileName)
        //     {
        //         const auto worker = new Worker;
        //         worker->startWork();
        //     }
        // }
    }

    PCWSTR nextFile()
    {
        if (pNext == nullptr)
        {
            pNext = wSelected;
            nIndex = 0;
        }
        pNext = wcschr(pNext, 0);
        if (pNext != nullptr)
        {
            nIndex++;
            pNext++;
            if (*pNext == 0)
            {
                pNext = nullptr;
            }
        }
        return pNext;
    }
};
