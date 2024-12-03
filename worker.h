#pragma once

#include "resource.h"

class Worker {
    HCRYPTPROV hCrypt = 0;

public:
    static void staticNew(HWND hDlg, PCSTR cPassword, PCWSTR wFileName, int isEncrypt) {
        const auto self = new Worker;
        QueueUserWorkItem(staticMain, self, 0);
    }

    static WINAPI DWORD staticMain(PVOID input) {
        const auto self = (Worker *) input;
        self->workerMain();
        delete self;
        return 0;
    }

    Worker() {
        if (!CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        }
    }

    ~Worker() {
        if (hCrypt != 0) {
            CryptReleaseContext(hCrypt, 0);
        }
    }

    void workerMain() {
    }


    //    HCRYPTKEY hKey = 0;
    //    HANDLE plainFile = nullptr;
    //    HANDLE secretFile = nullptr;
    //    BYTE bSalt[32] = {};
    //    BYTE bBuffer[4096] = {};
    //
    //public:
    //
    //    int decryptReadSalt()
    //    {
    //    }
    //
    //    int decryptVerifyKey()
    //    {
    //        DWORD readSize = 0;
    //        if (!ReadFile(secretFile, bSalt, 32, &readSize, nullptr))
    //        {
    //        }
    //        if (readSize != 32)
    //        {
    //        }
    //    }
    //
    //    int decryptMain()
    //    {
    //    }
    //
    //    int encryptGenSalt()
    //    {
    //    }
    //
    //    int encryptSignKey()
    //    {
    //    }
    //
    //    int encryptMain()
    //    {
    //        for (;;)
    //        {
    //            DWORD readSize = 0;
    //            if (!ReadFile(plainFile, bBuffer, 4096, &readSize, nullptr))
    //            {
    //            }
    //            if (!CryptDecrypt(hKey, 0, 0, 0, bBuffer, &readSize))
    //            {
    //            }
    //            DWORD writeSize = 0;
    //            if (!WriteFile(secretFile, bBuffer, readSize, &writeSize, nullptr))
    //            {
    //            }
    //            if (readSize != writeSize)
    //            {
    //            }
    //        }
    //    }
};
