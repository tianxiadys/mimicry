#pragma once
#include "resource.h"
#include "worker.h"

class Progress
{
    HCRYPTPROV hCrypt = 0;
    wchar_t wMessage[2000] = {};

public:
    Progress()
    {
        const auto result = CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, 0);
        if (!result)
        {
            const auto reason = GetLastError();
            swprintf_s(wMessage, L"初始化加密组件失败0x%X", reason);
            MessageBoxW(nullptr, wMessage, L"错误", 0);
        }
    }

    ~Progress()
    {
        if (hCrypt != 0)
        {
            CryptReleaseContext(hCrypt, 0);
        }
    }

    void messageInit(HWND hDlg)
    {
    }

    void startWork(PCSTR cPassword, PCWSTR wSelected, int isEncrypt)
    {
    }

    void addResult(int status, PCWSTR wError)
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
};
