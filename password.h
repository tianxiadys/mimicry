#pragma once
#include "resource.h"
#include <cstdint>

class Password
{
    HWND hDialog = nullptr;
    HWND hPassword = nullptr;
    wchar_t passwordW[50] = {};
    uint8_t passwordB[150] = {};

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hPassword = GetDlgItem(hDlg, ID_PASSWORD);
    }

    // Password(HWND hDlg)
    // {
    //     this->hDialog = hDlg;
    //     this->hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
    // }

    // void buttonShow()
    // {
    //     const auto isShow = IsDlgButtonChecked(hDialog, ID_D1_SHOW);
    //     SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
    //     InvalidateRect(hPassword, nullptr, 1);
    // }
    //
    // int inputPassword(HWND hDlg, wchar_t* output, int outputSize)
    // {
    //     const auto hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
    //     const auto realSize = GetDlgItemTextW(hDlg, ID_D1_PASSWORD, output, outputSize);
    //     if (realSize < 4)
    //     {
    //         EDITBALLOONTIP tips = {};
    //         tips.cbStruct = sizeof(EDITBALLOONTIP);
    //         tips.pszTitle = L"密码太短";
    //         tips.pszText = L"必须填写至少四位密码";
    //         tips.ttiIcon = TTI_ERROR;
    //         Edit_ShowBalloonTip(hPassword, &tips);
    //         return 0;
    //     }
    //     return 1;
    // }
};

// void buttonDecrypt(HWND hDlg)
// {
//     wchar_t passwordW[50];
//     const auto lengthW = inputPassword(hDlg, passwordW, 50);
// }
//
// void buttonEncrypt(HWND hDlg)
// {
//     wchar_t passwordW[50];
//     const auto lengthW = inputPassword(hDlg, passwordW, 50);
// }
//
// void buttonShow(HWND hDlg)
// {
//     const auto hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
//     const auto isShow = IsDlgButtonChecked(hDlg, ID_D1_SHOW);
//     SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
//     InvalidateRect(hPassword, nullptr, 1);
// }


//
// void messageClose()
// {
// }
//
// void messageCommand(UINT itemId)
// {
//     switch (itemId)
//     {
//     case ID_DECRYPT:
//         //buttonDecrypt(hDlg);
//             break;
//     case ID_ENCRYPT:
//         //buttonEncrypt(hDlg);
//             break;
//     case ID_SECRET:
//         buttonShow();
//         break;
//     default:
//         break;
//     }
// }
//
// void buttonShow()
// {
//     const auto isShow = IsDlgButtonChecked(hDialog, ID_SECRET);
//     SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
//     InvalidateRect(hPassword, nullptr, 1);
// }
//     //
//     // int inputPassword(HWND hDlg, wchar_t* output, int outputSize)
//     // {
//     //     const auto hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
//     //     const auto realSize = GetDlgItemTextW(hDlg, ID_D1_PASSWORD, output, outputSize);
//     //     if (realSize < 4)
//     //     {
//     //         EDITBALLOONTIP tips = {};
//     //         tips.cbStruct = sizeof(EDITBALLOONTIP);
//     //         tips.pszTitle = L"密码太短";
//     //         tips.pszText = L"必须填写至少四位密码";
//     //         tips.ttiIcon = TTI_ERROR;
//     //         Edit_ShowBalloonTip(hPassword, &tips);
//     //         return 0;
//     //     }
//     //     return 1;
//     // }
// };
//
// // void buttonDecrypt(HWND hDlg)
// // {
// //     wchar_t passwordW[50];
// //     const auto lengthW = inputPassword(hDlg, passwordW, 50);
// // }
// //
// // void buttonEncrypt(HWND hDlg)
// // {
// //     wchar_t passwordW[50];
// //     const auto lengthW = inputPassword(hDlg, passwordW, 50);
// // }
// //
// // void buttonShow(HWND hDlg)
// // {
// //     const auto hPassword = GetDlgItem(hDlg, ID_D1_PASSWORD);
// //     const auto isShow = IsDlgButtonChecked(hDlg, ID_D1_SHOW);
// //     SendMessageW(hPassword, EM_SETPASSWORDCHAR, isShow ? 0 : 0x25CF, 0);
// //     InvalidateRect(hPassword, nullptr, 1);
// // }
