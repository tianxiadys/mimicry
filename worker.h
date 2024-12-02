#pragma once
#include "resource.h"

class Worker
{
public:
    static WINAPI DWORD threadMain(PVOID lParam)
    {
        const auto self = (Worker*)lParam;
        self->threadRun();
        delete self;
    }

    void startWork()
    {
        QueueUserWorkItem(threadMain, this, 0);
    }

    void threadRun()
    {
    }
};
