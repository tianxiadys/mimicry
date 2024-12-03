#pragma once
#include "resource.h"

class Dialog
{
    HWND hDialog = nullptr;
    HWND hCheck = nullptr;
    HWND hDecrypt = nullptr;
    HWND hDetails = nullptr;
    HWND hEncrypt = nullptr;
    HWND hPassword = nullptr;
    HWND hProgress = nullptr;
    PCWSTR pNext = nullptr;
    int isEncrypt = 0;
    int nIndex = 0;
    int nTotal = 0;
    int nOpen = 0;
    int nClose = 0;
    wchar_t wPassword[48] = {};
    char cPassword[144] = {};
    wchar_t wCurrent[256] = {};
    wchar_t wSelected[8000] = {};

public:
    Dialog()
    {
        GetCurrentDirectoryW(260, wCurrent);
    }

    INT_PTR dialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
        hCheck = GetDlgItem(hDlg, ID_SHOW);
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
        hProgress = GetDlgItem(hDlg, ID_PROGRESS);
    }

    void messageCommand(WPARAM wParam)
    {
        switch (wParam)
        {
        case ID_DECRYPT:
        case ID_ENCRYPT:
            //progress.startWork(password, wParam);
            break;
        case ID_SHOW:
            buttonShow();
            break;
        default: ;
        }
    }

    void buttonShow()
    {
        const auto isShow = SendMessageW(hCheck, BM_GETCHECK, 0, 0);
        SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
        InvalidateRect(hPassword, nullptr, 1);
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

    int getSelected(int isEncrypt)
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
};

//
//     void setEnable(int isEnable)
//     {
//         EnableWindow(hDecrypt, isEnable);
//         EnableWindow(hEncrypt, isEnable);
//         EnableWindow(hPassword, isEnable);
//     }
//
//     void setProgress(int total, int open, int close)
//     {
//         wchar_t buffer[30];
//         swprintf_s(buffer, L"总数%d - 进行中%d - 完成%d", total, open, close);
//         SetWindowTextW(hDetails, buffer);
//         SendMessageW(hProgress, PBM_SETPOS, close * 100 / total, 0);
//     }
//
// public:
//     void messageInit(HWND hDlg)
//     {
//         hDialog = hDlg;
//         hPassword = GetDlgItem(hDlg, ID_PASSWORD);
//     }
//
//
// public:
//     void startWork(Password& password, WPARAM wParam)
//     {
//         memset(cPassword, 0, 144);
//         wmemset(wSelected, 0, 8000);
//         pNext = nullptr;
//         isEncrypt = wParam == ID_ENCRYPT;
//         nIndex = 0;
//         nTotal = 0;
//         nOpen = 0;
//         nClose = 0;
//         if (!password.getPassword(cPassword, 144))
//         {
//             return;
//         }
//         if (!password.getSelected(wSelected, 8000, isEncrypt))
//         {
//             return;
//         }
//         while (nextFile() != nullptr)
//         {
//             nTotal++;
//         }
//         SendMessageW(hDialog, APP_NEXT, 0, 0);
//     }
//
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
//
//     PCWSTR nextFile()
//     {
//         if (pNext == nullptr)
//         {
//             pNext = wSelected;
//             nIndex = 0;
//         }
//         pNext = wcschr(pNext, 0);
//         if (pNext != nullptr)
//         {
//             nIndex++;
//             pNext++;
//             if (*pNext == 0)
//             {
//                 pNext = nullptr;
//             }
//         }
//         return pNext;
//     }
//
// public:
