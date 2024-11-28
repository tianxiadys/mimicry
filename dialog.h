#pragma once
#include "control.h"
#include "password.h"
#include "progress.h"
#include "rc4.h"

class Dialog
{
    Control control = {};
    Password password = {};
    Progress progress = {};
    wchar_t passwordW[48] = {};
    wchar_t fileBuffer[4096] = {};
    wchar_t* fileNext = nullptr;
    int fileIndex = 0;
    int fileTotal = 0;

public:
    int dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            messageCommand(wParam, lParam);
            return 1;
        case WM_INITDIALOG:
            control.messageInit(hDlg);
            password.messageInit(hDlg);
            progress.messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }

    void messageCommand(WPARAM wParam, LPARAM lParam)
    {
        switch (wParam & 0xFFFF)
        {
        case ID_DECRYPT:
            buttonEncrypt(0);
            break;
        case ID_ENCRYPT:
            buttonEncrypt(1);
            break;
        case ID_SHOW:
            password.buttonShow();
            break;
        default:
            break;
        }
    }

    void buttonEncrypt(int isEncrypt)
    {
        wmemset(passwordW, 0, 48);
        wmemset(fileBuffer, 0, 4096);
        fileNext = nullptr;
        fileIndex = 0;
        fileTotal = 0;
        if (!password.getPassword(passwordW, 48))
        {
            return;
        }
        if (!control.getFileList(fileBuffer, 4096, isEncrypt))
        {
            return;
        }
        while (getNextFile() != nullptr)
        {
            fileTotal++;
        }
    }

    wchar_t* getNextFile()
    {
        if (fileNext == nullptr)
        {
            fileNext = fileBuffer;
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
