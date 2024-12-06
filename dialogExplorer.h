#pragma once

#include "resource.h"

class DialogExplorer {
    HWND hDialog = nullptr;
    wchar_t *pNext = nullptr;
    wchar_t wInitial[260] = {};
    wchar_t wOutput[260] = {};
    wchar_t wBuffer[8000] = {};

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;
        GetModuleFileNameW(nullptr, wInitial, 260);
        PathRemoveFileSpecW(wInitial);
    }

    int openFile(int bEncrypt) {
        *wBuffer = 0;
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = wBuffer;
        info.nMaxFile = 8000;
        info.lpstrInitialDir = wInitial;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
        if (!bEncrypt) {
            info.lpstrFilter = L"*.1\0*.1\0\0";
        }
        if (!GetOpenFileNameW(&info)) {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL) {
                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
            }
            return 0;
        }
        wBuffer[info.nFileOffset - 1] = 0;
        pNext = wBuffer;
        return 1;
    }

    int getTotal() {
        int total = 0;
        for (int i = 0; i < 8000; i++) {
            if (wBuffer[i] == 0) {
                if (wBuffer[i + 1] == 0) {
                    break;
                }
                total++;
            }
        }
        return total;
    }

    PCWSTR getNext() {
        if (pNext != nullptr) {
            pNext = wcschr(pNext, 0);
            if (pNext != nullptr) {
                pNext++;
                if (*pNext != 0) {
                    PathCombineW(wOutput, wBuffer, pNext);
                    return wOutput;
                } else {
                    pNext = nullptr;
                }
            }
        }
        return nullptr;
    }
};
