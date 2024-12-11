#pragma once

#include "resource.h"

class DialogExplorer {
    HWND hDialog = nullptr;
    PCWSTR pNext = nullptr;
    WCHAR wOutput[260] = {};
    WCHAR wBuffer[8000] = {};

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;;
    }

    int selectFile() {
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = wBuffer;
        info.nMaxFile = 8000;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
        if (!GetModuleFileNameW(nullptr, wBuffer, 260)) {
            return 0;
        }
        if (!PathRemoveFileSpecW(wBuffer)) {
            return 0;
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

    PCWSTR getNext() {
        if (pNext != nullptr) {
            pNext = wcschr(pNext, 0);
            if (pNext != nullptr) {
                pNext++;
                if (*pNext != 0) {
                    return PathCombineW(wOutput, wBuffer, pNext);
                } else {
                    pNext = nullptr;
                }
            }
        }
        return nullptr;
    }
};
