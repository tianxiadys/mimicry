#pragma once
#include "resource.h"
#include "worker.h"

class Progress
{
    HCRYPTPROV hCrypt = 0;
    HWND hDialog = nullptr;
    HWND hDetails = nullptr;
    HWND hProgress = nullptr;
    PCSTR pPassword = nullptr;
    PCWSTR pDirectory = nullptr;
    PCWSTR pCurrent = nullptr;
    wchar_t wMessage[2000] = {};

public:
    Progress()
    {
        const auto result = CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
        if (!result)
        {
            const auto reason = GetLastError();
            swprintf_s(wMessage, L"初始化加密组件失败（代码%d）", reason);
            MessageBoxW(nullptr, wMessage, L"错误", 0);
        }
    }

    ~Progress()
    {
        CryptReleaseContext(hCrypt, 0);
    }

    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
    }

    void messageClose(HWND hDlg)
    {
        EndDialog(hDlg, 0);
    }

    void startWork(PCSTR cPassword, PCWSTR wSelected, int isEncrypt)
    {
        pPassword = cPassword;
        pDirectory = wSelected;
        pCurrent = nullptr;
        wmemset(wMessage, 0, 2000);
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
