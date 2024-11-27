#pragma once

class Progress
{
    HWND hDialog = nullptr;
    HWND hProgress1 = nullptr;
    HWND hProgress2 = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hProgress1 = GetDlgItem(hDlg, ID_PROGRESS1);
        hProgress2 = GetDlgItem(hDlg, ID_PROGRESS2);
    }
};
