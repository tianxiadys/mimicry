#pragma once

#include "worker.h"

class Master {
    HWND hDialog = nullptr;
    Worker *first = nullptr;
    int next = 0;

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;
    }

    void startWorker(PCWSTR file, PCSTR key, WPARAM wParam) {
        const auto worker = new Worker;
        worker->next = first;
        first = worker;
        worker->runWorker(hDialog, file, key, wParam, next++);
    }

    Worker *removeClose() {
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
