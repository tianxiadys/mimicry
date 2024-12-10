#pragma once

#include "resource.h"

struct ExpKey {
    BLOBHEADER hdr;
    DWORD dwKeySize;
    BYTE rgbKeyData[];
};

class DialogWorker {
    HCRYPTPROV hCrypt = 0;

    static WINAPI DWORD staticMain(PVOID input) {
        const auto self = (DialogWorker *) input;
        self->workerMain();
        delete self;
        return 0;
    }

public:
    ~DialogWorker() {
        if (hCrypt) {
            CryptReleaseContext(hCrypt, 0);
        }
    }

    int workerInit() {
        if (!CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
            return 0;
        }
        {
            //SHA1
            HCRYPTHASH hHash = 0;
            BYTE inputData[20] = {49, 50, 51, 52, 53, 54};
            BYTE outputData[20] = {};
            DWORD outputSize = 20;
            wchar_t outputStr[100] = {};
            DWORD outputSize2 = 100;
            //
            CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash);
            CryptHashData(hHash, inputData, 6, 0);
            //CryptGetHashParam(hHash, HP_HASHVAL, outputData, &outputSize, 0);
            //CryptDestroyHash(hHash);
            //密钥派生
            HCRYPTKEY hKey = 0;
            BYTE expKey[500] = {};
            DWORD expSize = 500;
            BYTE realKey[32] = {};

            //
            CryptDeriveKey(hCrypt, CALG_AES_256, hHash, CRYPT_EXPORTABLE, &hKey);
            CryptExportKey(hKey, 0, PLAINTEXTKEYBLOB, 0, expKey, &expSize);
            //
            //DWORD dwMode = CRYPT_MODE_ECB;
            //CryptSetKeyParam(hKey, KP_MODE, (BYTE *) &dwMode, 0);
            //
            auto f1 = (ExpKey *) expKey;
            memcpy_s(realKey, 32, f1->rgbKeyData, 32);
            CryptBinaryToStringW(realKey, 32, CRYPT_STRING_HEX | CRYPT_STRING_NOCRLF, outputStr, &outputSize2);
            //
            BYTE encData[100] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 49, 50, 51, 52, 53, 54};
            DWORD encSize = 16;
            CryptEncrypt(hKey, 0, 0, 0, encData, &encSize, 100);
            //
            wchar_t outputStr2[100] = {};
            DWORD outputStr2Size = 100;
            CryptBinaryToStringW(encData, encSize, CRYPT_STRING_HEX | CRYPT_STRING_NOCRLF, outputStr2, &outputStr2Size);
            auto r = 0;
        }
        //
        return 1;
    }

    void workerStart() {
        QueueUserWorkItem(staticMain, this, 0);
    }

    void workerMain() {

    }
};
