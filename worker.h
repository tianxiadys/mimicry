#pragma once

#include "resource.h"

class Worker {
    HWND hDialog = nullptr;
    WPARAM command = 0;
    WCHAR inputFile[260] = {};
    WCHAR outputFile[260] = {};
    CHAR inputKey[144] = {};
    HCRYPTPROV hCrypt = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hKey = 0;
    BYTE bufferIV[16] = {};
    HANDLE hInput = nullptr;
    HANDLE hOutput = nullptr;

    static WINAPI DWORD staticMain(PVOID input) {
        const auto worker = (Worker *) input;
        worker->workerMain();
        return 0;
    }

    void workerMain() {
    }

    void postMessage() {
        PostMessageW(hDialog, APP_UPDATE, 0, (LPARAM) this);
    }

    int initCrypt() {
        return CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    }

    int initKey(PCBYTE pKey, int size) {
        if (!CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash)) {
            return 0;
        }
        if (!CryptHashData(hHash, pKey, size, 0)) {
            return 0;
        }
        if (!CryptDeriveKey(hCrypt, CALG_AES_256, hHash, 0, &hKey)) {
            return 0;
        }
        DWORD mode = CRYPT_MODE_OFB;
        if (!CryptSetKeyParam(hKey, KP_MODE, (PCBYTE) &mode, 0)) {
            return 0;
        }
        return 1;
    }

    int initIV(PCBYTE pIV, int size) {
        if (pIV != nullptr) {
            if (size == 16) {
                memcpy(bufferIV, pIV, 16);
            } else {
                return 0;
            }
        } else {
            if (!CryptGenRandom(hCrypt, 16, bufferIV)) {
                return 0;
            }
        }
        if (!CryptSetKeyParam(hKey, KP_IV, bufferIV, 0)) {
            return 0;
        }
        return 1;
    }

    int encryptData(PBYTE pData, int size) {
        return CryptEncrypt(hKey, 0, 0, 0, pData, (PDWORD) &size, size);
    }

    void releaseCrypt() {
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

    void closeFile() {
        if (hInput) {
            CloseHandle(hInput);
            hInput = nullptr;
        }
        if (hOutput) {
            CloseHandle(hOutput);
            hOutput = nullptr;
        }
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
    //
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
        command = wParam;
        wcscpy_s(inputFile, file);
        strcpy_s(inputKey, key);
        if (wParam == ID_ENCRYPT) {
            swprintf_s(column1, L"加密：%s", file);
            wcscpy_s(column2, L"等待");
        } else {
            swprintf_s(column1, L"解密：%s", file);
            wcscpy_s(column2, L"等待");
        }
    }

    void runWorker() {
        QueueUserWorkItem(staticMain, this, 0);
    }
};
