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
    CHAR inputKey[48] = {};
    WCHAR outputFile[260] = {};
    BYTE bufferIV[16] = {};
    BYTE bufferB1[16] = {};
    BYTE bufferData[8000] = {};

    static WINAPI DWORD staticMain(PVOID input) {
        const auto worker = (Worker *) input;
        if (worker->encrypt) {
            worker->encryptMain();
        } else {
            worker->decryptMain();
        }
        worker->releaseWorker();
        return 0;
    }

    void postProgress(double value) {
        swprintf_s(column2, L"进度：%.1f%%", value);
        postMessage();
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

    int initCrypt() {
        if (!CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, 0)) {
            postError();
            return 0;
        }
        return 1;
    }

    int initIV() {
        if (!CryptGenRandom(hCrypt, 16, bufferIV)) {
            postError();
            return 0;
        }
        return 1;
    }

    int initKey() {
        if (!CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash)) {
            postError();
            return 0;
        }
        if (!CryptHashData(hHash, bufferIV, 16, 0)) {
            postError();
            return 0;
        }
        DWORD keySize = strlen(inputKey);
        if (!CryptHashData(hHash, (PCBYTE) inputKey, keySize, 0)) {
            postError();
            return 0;
        }
        if (!CryptDeriveKey(hCrypt, CALG_AES_256, hHash, 0, &hKey)) {
            postError();
            return 0;
        }
        if (!CryptSetKeyParam(hKey, KP_IV, bufferIV, 0)) {
            postError();
            return 0;
        }
        return 1;
    }

    int openFile() {
        hInput = CreateFileW(inputFile, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
        if (hInput == INVALID_HANDLE_VALUE) {
            postError();
            return 0;
        }
        fileSize = GetFileSize(hInput, nullptr);
        if (fileSize == 0) {
            postIgnore(L"输入文件长度为零");
            return 0;
        }
        hOutput = CreateFileW(outputFile, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
        if (hOutput == INVALID_HANDLE_VALUE) {
            postError();
            return 0;
        }
        return 1;
    }

    int encryptFile() {
        if (PathMatchSpecW(inputFile, L"*.exe")) {
            postIgnore(L"不能加密exe文件");
            return 0;
        }
        if (PathMatchSpecW(inputFile, L"*.dll")) {
            postIgnore(L"不能加密dll文件");
            return 0;
        }
        wcscat_s(outputFile, L".1");
        return 1;
    }

    int encryptHead() {
        if (!initIV()) {
            return 0;
        }
        if (!initKey()) {
            return 0;
        }
        memcpy_s(bufferB1, 16, bufferIV, 16);
        DWORD realSize = 16;
        if (!CryptEncrypt(hKey, 0, 0, 0, bufferB1, &realSize, 16)) {
            postError();
            return 0;
        }
        if (!WriteFile(hOutput, bufferIV, 16, &realSize, nullptr)) {
            postError();
            return 0;
        }
        if (!WriteFile(hOutput, bufferB1, 16, &realSize, nullptr)) {
            postError();
            return 0;
        }
        return 1;
    }

    int encryptBlock() {
        DWORD realSize = 0;
        if (!ReadFile(hInput, bufferData, 8000, &realSize, nullptr)) {
            postError();
            return 0;
        }
        if (realSize == 0) {
            if (!CryptEncrypt(hKey, 0, 1, 0, bufferData, &realSize, 8000)) {
                postError();
                return 0;
            }
            if (!WriteFile(hOutput, bufferData, realSize, &realSize, nullptr)) {
                postError();
                return 0;
            }
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

    void encryptMain() {
        if (!initCrypt()) {
            return;
        }
        if (!encryptFile()) {
            return;
        }
        if (!openFile()) {
            return;
        }
        if (!encryptHead()) {
            return;
        }
        DWORD realSize = 0;
        DWORD loopSize = 0;
        while (encryptBlock()) {
            realSize += 8000;
            loopSize += 1;
            if (loopSize > 1000) {
                loopSize = 0;
                postProgress(realSize * 100.0 / fileSize);
            }
        }
    }

    int decryptFile() {
        if (!PathMatchSpecW(inputFile, L"*.1")) {
            postIgnore(L"不是加密文件");
            return 0;
        }
        PathRemoveExtensionW(outputFile);
        return 1;
    }

    int decryptHead() {
        DWORD readSize = 0;
        if (!ReadFile(hInput, bufferData, 32, &readSize, nullptr)) {
            postError();
            return 0;
        }
        if (readSize != 32) {
            postError(L"加密文件长度太短");
            return 0;
        }
        memcpy_s(bufferIV, 16, bufferData, 16);
        memcpy_s(bufferB1, 16, bufferData + 16, 16);
        if (!initKey()) {
            return 0;
        }
        readSize = 16;
        if (!CryptDecrypt(hKey, 0, 0, 0, bufferB1, &readSize)) {
            postError();
            return 0;
        }
        if (memcmp(bufferIV, bufferB1, 16) != 0) {
            postError(L"密码错误");
            return 0;
        }
        return 1;
    }

    int decryptBlock() {
        DWORD realSize = 0;
        if (!ReadFile(hInput, bufferData, 8000, &realSize, nullptr)) {
            postError();
            return 0;
        }
        if (realSize == 0) {
            if (!CryptDecrypt(hKey, 0, 1, 0, bufferData, &realSize)) {
                postError();
                return 0;
            }
            if (!WriteFile(hOutput, bufferData, realSize, &realSize, nullptr)) {
                postError();
                return 0;
            }
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

    void decryptMain() {
        if (!initCrypt()) {
            return;
        }
        if (!decryptFile()) {
            return;
        }
        if (!openFile()) {
            return;
        }
        if (!decryptHead()) {
            return;
        }
        DWORD realSize = 0;
        DWORD loopSize = 0;
        while (decryptBlock()) {
            realSize += 8000;
            loopSize += 1;
            if (loopSize > 1000) {
                loopSize = 0;
                postProgress(realSize * 100.0 / fileSize);
            }
        }
    }

    void releaseWorker() {
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
        wcscpy_s(outputFile, file);
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
