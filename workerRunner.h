#pragma once

#include "workerCrypto.h"

class WorkerRunner {
    WorkerCrypto crypto = {};
    
public:
    WorkerRunner *next = nullptr;
};
