#pragma once

#include "resource.h"
#include "workerRC4.h"

class Worker {
    WorkerRC4 rc4 = {};
    HWND hDialog = nullptr;
    HANDLE hInput = nullptr;
    HANDLE hOutput = nullptr;
    DWORD fileSize = 0;
    WCHAR inputFile[260] = {};
    WCHAR outputFile[260] = {};
    BYTE bufferData[8000] = {};

    static WINAPI DWORD staticMain(PVOID input) {
        const auto worker = (Worker *) input;
        if (worker->encrypt) {
            worker->encryptMain();
        } else {
            worker->decryptMain();
        }
        worker->closeFile();
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

    int encryptPath() {
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
        DWORD realSize = 0;
        rc4.encryptZero(bufferData, 16);
        if (!WriteFile(hOutput, bufferData, 16, &realSize, nullptr)) {
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
            postSuccess();
            return 0;
        }
        rc4.encryptData(bufferData, realSize);
        if (!WriteFile(hOutput, bufferData, realSize, &realSize, nullptr)) {
            postError();
            return 0;
        }
        return 1;
    }

    void encryptMain() {
        if (!encryptPath()) {
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

    int decryptPath() {
        if (!PathMatchSpecW(inputFile, L"*.1")) {
            postIgnore(L"不是加密文件");
            return 0;
        }
        PathRemoveExtensionW(outputFile);
        return 1;
    }

    int decryptHead() {
        DWORD readSize = 0;
        if (!ReadFile(hInput, bufferData, 16, &readSize, nullptr)) {
            postError();
            return 0;
        }
        if (readSize != 16) {
            postError(L"加密文件长度太短");
            return 0;
        }
        if (!rc4.verifyZero(bufferData, 16)) {
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
            postSuccess();
            return 0;
        }
        rc4.encryptData(bufferData, realSize);
        if (!WriteFile(hOutput, bufferData, realSize, &realSize, nullptr)) {
            postError();
            return 0;
        }
        return 1;
    }

    void decryptMain() {
        if (!decryptPath()) {
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
        rc4.initKey(key);
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
