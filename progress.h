#pragma once
#include "resource.h"

class Progress
{
    HWND hText1 = nullptr;
    HWND hText2 = nullptr;
    HWND hProgress1 = nullptr;
    HWND hProgress2 = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hText1 = GetDlgItem(hDlg, ID_TEXT1);
        hText2 = GetDlgItem(hDlg, ID_TEXT2);
        hProgress1 = GetDlgItem(hDlg, ID_PROGRESS1);
        hProgress2 = GetDlgItem(hDlg, ID_PROGRESS2);
    }

    void setProgress1(int current, int total)
    {
        wchar_t buffer[20];
        swprintf_s(buffer, L"全部：%d/%d", current, total);
        SetWindowTextW(hText1, buffer);
        SendMessageW(hProgress1, PBM_SETPOS, current * 100 / total, 0);
    }

    void setProgress2(int current, int total, PCWSTR fileName)
    {
        wchar_t buffer[90];
        swprintf_s(buffer, L"当前：%s", fileName);
        SetWindowTextW(hText2, buffer);
        SendMessageW(hProgress2, PBM_SETPOS, current * 100 / total, 0);
    }
};
