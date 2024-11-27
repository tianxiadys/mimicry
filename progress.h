#pragma once

class Progress
{
    HWND hDialog = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
    }

    void setProgress1(int index, int total)
    {
        wchar_t text[30];
        wsprintfW(text, L"全部：%d/%d", index, total);
        SetDlgItemTextW(hDialog, ID_TEXT1, text);
        SendDlgItemMessageW(hDialog, ID_PROGRESS1, PBM_SETPOS, index * 100 / total, 0);
    }
};
