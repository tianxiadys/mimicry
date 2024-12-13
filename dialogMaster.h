#pragma once

#include "dialogWorker.h"

class DialogMaster {
    HWND hDialog = nullptr;
    DialogWorker *first = nullptr;

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;
    }

    void newEncrypt(PCWSTR file, PCSTR key) {
    }

    void newDecrypt(PCWSTR file, PCSTR key) {
    }

    DialogWorker *removeClose() {
        auto before = first;
        auto current = first;
        while (current != nullptr) {
            if (current->close) {
                if (before == first) {
                    first = current->next;
                } else {
                    before->next = current->next;
                }
                return current;
            } else {
                before = current;
                current = current->next;
            }
        }
        return nullptr;
    }
};
