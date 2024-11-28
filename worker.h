#pragma once

class Worker
{
    wchar_t* fileNext = nullptr;
    int fileIndex = 0;
    int fileTotal = 0;

public:
    // wchar_t* getNextFile()
    // {
    //     if (fileNext == nullptr)
    //     {
    //         fileNext = fileBuffer;
    //         fileIndex = 0;
    //     }
    //     fileNext = wcschr(fileNext, 0);
    //     if (fileNext != nullptr)
    //     {
    //         fileIndex++;
    //         fileNext++;
    //         if (*fileNext == 0)
    //         {
    //             fileNext = nullptr;
    //         }
    //     }
    //     return fileNext;
    // }
    //
    // void resetWorker()
    // {
    //     wmemset(fileBuffer, 0, 4096);
    //     fileNext = nullptr;
    //     fileIndex = 0;
    //     fileTotal = 0;
    // }
};
