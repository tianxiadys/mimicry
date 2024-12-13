#pragma once

#include "resource.h"

class Worker {
    HWND hDialog = nullptr;
    HCRYPTPROV hCrypt = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hKey = 0;
    BYTE bufferIV[16] = {};

    static WINAPI DWORD staticMain(PVOID input) {
        const auto worker = (Worker *) input;
        worker->workerMain();
        return 0;
    }

    void workerMain() {
        postMessage();
    }

    void postMessage() {
        PostMessageW(hDialog, APP_UPDATE, 0, (LPARAM) this);
    }
    //
    //
    //    int startWork(HWND hDlg) {
    //        hDialog = hDlg;
    //        return QueueUserWorkItem(staticMain, this, 0);
    //    }
    //#pragma once
    //
    //class WorkerCrypto {
    //
    //public:
    //    ~WorkerCrypto() {
    //        releaseCrypt();
    //    }
    //
    //    int initCrypt() {
    //        return CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    //    }
    //
    //    int initKey(PCBYTE pKey, int size) {
    //        if (!CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash)) {
    //            return 0;
    //        }
    //        if (!CryptHashData(hHash, pKey, size, 0)) {
    //            return 0;
    //        }
    //        if (!CryptDeriveKey(hCrypt, CALG_AES_256, hHash, 0, &hKey)) {
    //            return 0;
    //        }
    //        DWORD mode = CRYPT_MODE_OFB;
    //        if (!CryptSetKeyParam(hKey, KP_MODE, (PCBYTE) &mode, 0)) {
    //            return 0;
    //        }
    //        return 1;
    //    }
    //
    //    int initIV(PCBYTE pIV, int size) {
    //        if (pIV != nullptr) {
    //            if (size == 16) {
    //                memcpy(bufferIV, pIV, 16);
    //            } else {
    //                return 0;
    //            }
    //        } else {
    //            if (!CryptGenRandom(hCrypt, 16, bufferIV)) {
    //                return 0;
    //            }
    //        }
    //        if (!CryptSetKeyParam(hKey, KP_IV, bufferIV, 0)) {
    //            return 0;
    //        }
    //        return 1;
    //    }
    //
    //    void releaseCrypt() {
    //        if (hHash) {
    //            CryptDestroyHash(hHash);
    //            hHash = 0;
    //        }
    //        if (hKey) {
    //            CryptDestroyKey(hKey);
    //            hKey = 0;
    //        }
    //        if (hCrypt) {
    //            CryptReleaseContext(hCrypt, 0);
    //            hCrypt = 0;
    //        }
    //    }
    //
    //    int encryptData(PBYTE pData, int size) {
    //        return CryptEncrypt(hKey, 0, 0, 0, pData, (PDWORD) &size, size);
    //    }
    //
    //    PCBYTE getIV() {
    //        return bufferIV;
    //    }
    //};

public:
    Worker *next = nullptr;
    int index = 0;
    int success = 0;
    WCHAR column1[260] = {};
    WCHAR column2[300] = {};

    void initWorker(HWND hDlg, PCWSTR file, PCSTR key, WPARAM wParam) {
        hDialog = hDlg;
        StringCchCopyW(column2, 300, L"等待");
        if (wParam == ID_ENCRYPT) {
            StringCchPrintfW(column1, 260, L"加密：%s", file);
        } else {
            StringCchPrintfW(column1, 260, L"解密：%s", file);
        }
    }

    void runWorker() {
        QueueUserWorkItem(staticMain, this, 0);
    }
};
