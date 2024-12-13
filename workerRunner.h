#pragma once

#include "workerCrypto.h"

class WorkerRunner {
    WorkerCrypto crypto = {};

public:
    WorkerRunner *next = nullptr;
    int index = 0;
    int finish = 0;
};
