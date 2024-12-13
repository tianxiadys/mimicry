#pragma once

#include "worker.h"

class Master {
    HWND hDialog = nullptr;
    Worker *pFirst = nullptr;

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;
    }

    void startWorker(PCWSTR file, PCSTR key, WPARAM wParam) {
        const auto worker = new Worker;
        if (pFirst) {
            worker->index = pFirst->index + 1;
            worker->next = pFirst;
        }
        pFirst = worker;
        worker->initWorker(hDialog, file, key, wParam);
        worker->runWorker();
    }

    Worker *removeSucceed() {
        auto before = pFirst;
        auto current = pFirst;
        while (current != nullptr) {
            if (current->success) {
                if (before == pFirst) {
                    pFirst = current->next;
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
