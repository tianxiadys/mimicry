#pragma once
#include "control.h"
#include "password.h"

class Progress
{
    Password& password;
    Control& control;
    HWND hDialog = nullptr;
    PCWSTR fileNext = nullptr;
    int fileIndex = 0;
    int fileTotal = 0;
    int isEncrypt = 0;

public:
    Progress(Password& _password, Control& _control): password(_password), control(_control)
    {
    }

    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
    }

    void startWork(, int _isEncrypt)
    {
        memset(cPassword, 0, 144);
        wmemset(wSelected, 0, 8000);
        fileNext = nullptr;
        fileIndex = 0;
        fileTotal = 0;
        isEncrypt = _isEncrypt;
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
            fileTotal++;
        }
        nextWorker();
    }

    void nextWork()
    {
    }

    PCWSTR nextFile()
    {
        if (fileNext == nullptr)
        {
            fileNext = wSelected;
            fileIndex = 0;
        }
        fileNext = wcschr(fileNext, 0);
        if (fileNext != nullptr)
        {
            fileIndex++;
            fileNext++;
            if (*fileNext == 0)
            {
                fileNext = nullptr;
            }
        }
        return fileNext;
    }
};
