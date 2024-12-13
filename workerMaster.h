#pragma once

#include "workerRunner.h"

class WorkerMaster {
    WorkerRunner *first = nullptr;

public:
    WorkerRunner *removeFinish() {
        auto before = first;
        auto current = first;
        while (current != nullptr) {
            if (current->finish) {
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
