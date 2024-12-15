#pragma once

#include "resource.h"

class Worker {
    HWND hDialog = nullptr;
    HCRYPTPROV hCrypt = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hKey = 0;
    HANDLE hInput = nullptr;
    HANDLE hOutput = nullptr;
    DWORD fileSize = 0;
    WCHAR inputFile[260] = {};
    WCHAR outputFile[260] = {};
    CHAR inputKey[144] = {};
    BYTE bufferIV[16] = {};
    BYTE bufferKey[160] = {};
    BYTE bufferData[8000] = {};

    static WINAPI DWORD staticMain(PVOID input) {
        const auto worker = (Worker *) input;
        worker->workerMain();
        worker->workerRelease();
        return 0;
    }

    void workerMain() {
        if (!initCrypt()) {
            return;
        }
    }

    void workerRelease() {
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
        if (hInput) {
            CloseHandle(hInput);
            hInput = nullptr;
        }
        if (hOutput) {
            CloseHandle(hOutput);
            hOutput = nullptr;
        }
    }

    int initCrypt() {
        if (!CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
            postError();
            return 0;
        }
        return 1;
    }

    int initKey(PCBYTE pKey, int size) {
        if (!CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash)) {
            postError();
            return 0;
        }
        if (!CryptHashData(hHash, pKey, size, 0)) {
            postError();
            return 0;
        }
        if (!CryptDeriveKey(hCrypt, CALG_AES_256, hHash, 0, &hKey)) {
            postError();
            return 0;
        }
        DWORD mode = CRYPT_MODE_OFB;
        if (!CryptSetKeyParam(hKey, KP_MODE, (PCBYTE) &mode, 0)) {
            postError();
            return 0;
        }
        return 1;
    }

    int initIV(PCBYTE pIV, int size) {
        if (pIV != nullptr) {
            if (size == 16) {
                memcpy(bufferIV, pIV, 16);
            } else {
                postError(L"IV长度错误");
                return 0;
            }
        } else {
            if (!CryptGenRandom(hCrypt, 16, bufferIV)) {
                postError();
                return 0;
            }
        }
        if (!CryptSetKeyParam(hKey, KP_IV, bufferIV, 0)) {
            postError();
            return 0;
        }
        return 1;
    }

    int openFile() {
        hInput = CreateFileW(inputFile, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
        if (!hInput) {
            postError();
            return 0;
        }
        fileSize = GetFileSize(hInput, nullptr);
        if (!fileSize) {
            postIgnore(L"输入文件长度为零");
            return 0;
        }
        hOutput = CreateFileW(outputFile, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, 0, nullptr);
        if (!hOutput) {
            postError();
            return 0;
        }
        return 1;
    }

    int encryptBlock() {
        DWORD realSize = 8000;
        if (!ReadFile(hInput, bufferData, 8000, &realSize, nullptr)) {
            postError();
            return 0;
        }
        if (realSize == 0) {
            postSuccess();
            return 0;
        }
        if (!CryptEncrypt(hKey, 0, 0, 0, bufferData, &realSize, 8000)) {
            postError();
            return 0;
        }
        if (!WriteFile(hOutput, bufferData, realSize, &realSize, nullptr)) {
            postError();
            return 0;
        }
        return 1;
    }

    int decryptBlock() {
        DWORD realSize = 8000;
        if (!ReadFile(hInput, bufferData, 8000, &realSize, nullptr)) {
            postError();
            return 0;
        }
        if (realSize == 0) {
            postSuccess();
            return 0;
        }
        if (!CryptDecrypt(hKey, 0, 0, 0, bufferData, &realSize)) {
            postError();
            return 0;
        }
        if (!WriteFile(hOutput, bufferData, realSize, &realSize, nullptr)) {
            postError();
            return 0;
        }
        return 1;
    }

    void postSuccess() {
        success = 1;
        wcscpy_s(column2, L"成功");
        postMessage();
    }

    void postIgnore(PCWSTR message) {
        success = 1;
        swprintf_s(column2, L"忽略：%s", message);
        postMessage();
    }

    void postError() {
        const auto errorId = GetLastError();
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, errorId, 0, column2, 300, nullptr);
        postMessage();
    }

    void postError(PCWSTR message) {
        swprintf_s(column2, L"错误：%s", message);
        postMessage();
    }

    void postMessage() {
        PostMessageW(hDialog, APP_UPDATE, 0, (LPARAM) this);
    }

public:
    Worker *next = nullptr;
    int encrypt = 0;
    int index = 0;
    int success = 0;
    WCHAR column1[260] = {};
    WCHAR column2[300] = {};

    void initWorker(HWND hDlg, PCWSTR file, PCSTR key, WPARAM wParam) {
        hDialog = hDlg;
        wcscpy_s(inputFile, file);
        strcpy_s(inputKey, key);
        if (wParam == ID_ENCRYPT) {
            encrypt = 1;
            swprintf_s(column1, L"加密：%s", file);
        } else {
            encrypt = 0;
            swprintf_s(column1, L"解密：%s", file);
        }
    }

    void runWorker() {
        QueueUserWorkItem(staticMain, this, 0);
    }
};
