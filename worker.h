#pragma once
#include "resource.h"

class Worker
{
public:
    static WINAPI DWORD staticMain(PVOID input)
    {
        const auto self = (Worker*)input;
        self->threadMain();
        delete self;
        return 0;
    }

    void startWork()
    {
        QueueUserWorkItem(staticMain, this, 0);
    }

    void threadMain()
    {
    }
};
