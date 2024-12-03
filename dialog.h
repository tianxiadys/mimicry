#pragma once
#include "worker.h"

class Dialog
{
    HWND hDialog = nullptr;
    HWND hDecrypt = nullptr;
    HWND hDetails = nullptr;
    HWND hEncrypt = nullptr;
    HWND hMask = nullptr;
    HWND hPassword = nullptr;
    HWND hProgress = nullptr;
    PCWSTR pNext = nullptr;
    int isEncrypt = 0;
    int nIndex = 0;
    int nTotal = 0;
    wchar_t wPassword[48] = {};
    char cPassword[144] = {};
    wchar_t wCurrent[260] = {};
    wchar_t wSelected[8000] = {};

public:
    Dialog()
    {
        GetCurrentDirectoryW(260, wCurrent);
    }

    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case APP_NEXT:
            //progress.nextWork(control, wParam);
            return 1;
        case WM_CLOSE:
            EndDialog(hDlg, 0);
            return 1;
        case WM_COMMAND:
            messageCommand(wParam);
            return 1;
        case WM_INITDIALOG:
            messageInit(hDlg);
            return 1;
        default:
            return 0;
        }
    }

    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
        hMask = GetDlgItem(hDlg, ID_MASK);
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
    }

    void messageCommand(WPARAM wParam)
    {
        switch (wParam)
        {
        case ID_DECRYPT:
            {
                isEncrypt = 0;
                startWork();
                break;
            }
        case ID_ENCRYPT:
            {
                isEncrypt = 1;
                startWork();
                break;
            }
        case ID_MASK:
            {
                const auto isShow = SendMessageW(hMask, BM_GETCHECK, 0, 0);
                setMask((int)isShow);
                break;
            }
        default: ;
        }
    }

    int getPassword()
    {
        const auto count = GetWindowTextW(hPassword, wPassword, 48);
        if (count < 4)
        {
            getPasswordTips(L"至少填写四位密码", L"密码太短");
            return 0;
        }
        if (count > 40)
        {
            getPasswordTips(L"至多填写四十位密码", L"密码太长");
            return 0;
        }
        WideCharToMultiByte(CP_UTF8, 0, wPassword, -1, cPassword, 144, nullptr, nullptr);
        return 1;
    }

    void getPasswordTips(PCWSTR text, PCWSTR title)
    {
        EDITBALLOONTIP info = {};
        info.cbStruct = sizeof(EDITBALLOONTIP);
        info.pszTitle = title;
        info.pszText = text;
        info.ttiIcon = TTI_WARNING;
        SendMessageW(hPassword, EM_SHOWBALLOONTIP, 0, (LPARAM)&info);
    }

    int getSelected()
    {
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.hwndOwner = hDialog;
        info.lpstrFile = wSelected;
        info.nMaxFile = 8000;
        info.lpstrInitialDir = wCurrent;
        info.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON;
        if (!isEncrypt)
        {
            info.lpstrFilter = L"*.1\0*.1\0\0";
        }
        if (!GetOpenFileNameW(&info))
        {
            const auto reason = CommDlgExtendedError();
            if (reason == FNERR_BUFFERTOOSMALL)
            {
                MessageBoxW(hDialog, L"选择的文件太多了", L"错误", 0);
            }
            return 0;
        }
        return 1;
    }

    void setEnable(int isEnable)
    {
        EnableWindow(hDecrypt, isEnable);
        EnableWindow(hEncrypt, isEnable);
        EnableWindow(hPassword, isEnable);
    }

    void setMask(int isShow)
    {
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
    }

    void setProgress(int total, int open, int close)
    {
        wchar_t buffer[30];
        swprintf_s(buffer, L"总数%d - 进行中%d - 完成%d", total, open, close);
        SetWindowTextW(hDetails, buffer);
        SendMessageW(hProgress, PBM_SETPOS, close * 100 / total, 0);
    }

    void jobStart()
    {
        memset(cPassword, 0, 144);
        wmemset(wSelected, 0, 8000);
        pNext = nullptr;
        nIndex = 0;
        nTotal = 0;
        if (!getPassword())
        {
            return;
        }
        if (!getSelected())
        {
            return;
        }
    }

    //     void nextWork(Control& control, WPARAM wParam)
    //     {
    //         // if (wParam == 0)
    //         // {
    //         //     control.setEnable(0);
    //         // }
    //         // for (; nOpen < 5; nOpen++)
    //         // {
    //         //     const auto fileName = nextFile();
    //         //     if (fileName)
    //         //     {
    //         //         const auto worker = new Worker;
    //         //         worker->startWork();
    //         //     }
    //         // }
    //     }
};
