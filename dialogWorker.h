#pragma once

#include "workerCrypto.h"

class DialogWorker {
    WorkerCrypto crypto = {};

public:
    HWND hDialog = nullptr;
    DialogWorker *next = nullptr;
    int index = 0;
    int close = 0;

    int initWorker() {

    }

    void threadMain() {

    }

    static WINAPI DWORD staticMain(PVOID input) {
        const auto self = (DialogWorker *) input;
        self->threadMain();
        return 0;
    }

    int startWork(HWND hDlg) {
        hDialog = hDlg;
        return QueueUserWorkItem(staticMain, this, 0);
    }
};
//#pragma once
//
//class WorkerCrypto {
//    HCRYPTPROV hCrypt = 0;
//    HCRYPTHASH hHash = 0;
//    HCRYPTKEY hKey = 0;
//    BYTE bufferIV[16] = {};
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