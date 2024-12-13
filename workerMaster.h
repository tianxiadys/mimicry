#pragma once

#include "workerRunner.h"

class WorkerMaster {
    HWND hDialog = nullptr;
    WorkerRunner *first = nullptr;

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;;
    }

    void startEncrypt(PCWSTR, PCSTR) {

    }

    void startDecrypt(PCWSTR, PCSTR) {

    }

    WorkerRunner *removeClose() {
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
