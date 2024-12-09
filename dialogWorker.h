#pragma once

#include "resource.h"

class DialogWorker {
    HCRYPTPROV hCrypt = 0;

    ~DialogWorker() {
        if (hCrypt) {
            CryptReleaseContext(hCrypt, 0);
        }
    }

    static WINAPI DWORD staticMain(PVOID input) {
        const auto self = (DialogWorker *) input;
        self->workerMain();
        delete self;
        return 0;
    }

public:
    int workerInit() {
        if (!CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
            return 0;
        }
        return 1;
    }

    void workerStart() {
        QueueUserWorkItem(staticMain, this, 0);
    }

    void workerMain() {

    }
};
