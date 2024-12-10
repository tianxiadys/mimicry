#pragma once

#include "resource.h"

class DialogWorker {
    HCRYPTPROV hCrypt = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hKey = 0;

    static WINAPI DWORD staticMain(PVOID input) {
        const auto self = (DialogWorker *) input;
        self->workerMain();
        delete self;
        return 0;
    }

public:
    ~DialogWorker() {
        cryptoRelease();
    }

    int cryptoInit(PCSTR cPassword) {
        cryptoRelease();
        if (!CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
            return 0;
        }
        if (!CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash)) {
            return 0;
        }
        const auto cSize = strlen(cPassword);
        if (!CryptHashData(hHash, (PBYTE) cPassword, cSize, 0)) {
            return 0;
        }
        if (!CryptDeriveKey(hCrypt, CALG_AES_256, hHash, 0, &hKey)) {
            return 0;
        }
        return 1;
    }

    void cryptoRelease() {
        if (hHash) {
            CryptDestroyHash(hHash);
            hHash = 0;
        }
        if (hKey) {
            CryptDestroyKey(hKey);
            hKey = 0;
        }
        if (hCrypt) {
            CryptReleaseContext(hCrypt, 0);
            hCrypt = 0;
        }
    }

    void workerStart() {
        QueueUserWorkItem(staticMain, this, 0);
    }

    void workerMain() {

    }
};
