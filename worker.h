#pragma once
#include "resource.h"

class Worker
{
    //    uint8_t K[32] = {};
    //    uint8_t S[256] = {};
    //    int i = 0;
    //    int j = 0;
    //
    //public:
    //    RC4(const uint8_t* password, const int size)
    //    {
    //        for (int x = 0; x < 32; x++)
    //        {
    //            K[x] = x * 8;
    //        }
    //        for (int x = 0; x < 256; x++)
    //        {
    //            S[x] = x;
    //        }
    //        if (size > 32)
    //        {
    //            for (int x = 0; x < size; x++)
    //            {
    //                K[x % 32] ^= password[x];
    //            }
    //        }
    //        else
    //        {
    //            for (int x = 0; x < 32; x++)
    //            {
    //                K[x] ^= password[x % size];
    //            }
    //        }
    //        for (int x = 0, y = 0; x < 256; x++)
    //        {
    //            y = y + S[x] + K[x % 32] & 0xFF;
    //            const auto temp = S[x];
    //            S[x] = S[y];
    //            S[y] = temp;
    //        }
    //    }
    //
    //    uint8_t getNext()
    //    {
    //        i = i + 1 & 0xFF;
    //        j = j + S[i] & 0xFF;
    //        const auto temp = S[i];
    //        S[i] = S[j];
    //        S[j] = temp;
    //        return S[S[i] + S[j] & 0xFF];
    //    }
    //    HWND hDialog = nullptr;
    //
    //public:
    //    void messageInit(HWND hDlg)
    //    {
    //        hDialog = hDlg;
    //    }
    //
    //    void startWorker(PCWSTR passwordW, PCWSTR fileListW, int isEncrypt)
    //    {
    //    }
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
