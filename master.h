#pragma once

#include "worker.h"

class Master {
    HWND hDialog = nullptr;
    Worker *first = nullptr;

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;
    }

    void startWorker(PCWSTR file, PCSTR key, WPARAM wParam) {
        const auto worker = new Worker;
        if (first) {
            worker->index = first->index + 1;
        }
        worker->next = first;
        first = worker;
    }

    Worker *removeClosed() {
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
