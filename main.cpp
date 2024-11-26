#include <windows.h>
#include <cwchar>
#include "rc4.hpp"
#include "resource.h"

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    // switch (message)
    // {
    // case WM_INITDIALOG: // 对话框初始化
    //     return TRUE;
    //
    // case WM_COMMAND: // 按钮事件
    //     switch (LOWORD(wParam))
    //     {
    //     case IDOK: // OK 按钮
    //         EndDialog(hDlg, IDOK);
    //         return TRUE;
    //     case IDCANCEL: // Cancel 按钮
    //         EndDialog(hDlg, IDCANCEL);
    //         return TRUE;
    //     }
    //     break;
    //
    // case WM_CLOSE: // 关闭对话框
    //     EndDialog(hDlg, 0);
    //     return TRUE;
    // }
    return FALSE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    DialogBox(hInstance, MAKEINTRESOURCE(ID_DIALOG_MAIN), NULL, DialogProc);
    return 0;
}
