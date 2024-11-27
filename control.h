#pragma once
#include "resource.h"

class Control
{
    HWND hDialog = nullptr;
    HWND hDecrypt = nullptr;
    HWND hEncrypt = nullptr;

public:
    void messageInit(HWND hDlg)
    {
        hDialog = hDlg;
        hDecrypt = GetDlgItem(hDlg, ID_DECRYPT);
        hEncrypt = GetDlgItem(hDlg, ID_ENCRYPT);
    }

    void messageEnable(int bEnable)
    {
        EnableWindow(hDecrypt, bEnable);
        EnableWindow(hEncrypt, bEnable);
    }

    void buttonEncrypt(int bEncrypt)
    {
        wchar_t buffer[1000];
        OPENFILENAMEW info = {};
        info.lStructSize = sizeof(OPENFILENAMEW);
        info.lpstrFile = buffer;
        info.nMaxFile = 1000;
        GetOpenFileNameW(&info);
        //     IFileDialog* pfd = nullptr;
        //     if (CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))
        //     {
        //         goto _finally;
        //     }
        //     if (!bEncrypt)
        //     {
        //         if (pfd->SetDefaultExtension(L"x1"))
        //         {
        //             goto _finally;
        //         }
        //     }
        //     if (pfd->Show(hDialog))
        //     {
        //         goto _finally;
        //     }
        // _finally:
        //     if (pfd)
        //     {
        //         pfd->Release();
        //     }
        //
        // pfd->Show(hDialog);

        // if (SUCCEEDED(hr))
        // {
        //     // Create an event handling object, and hook it up to the dialog.
        //     IFileDialogEvents* pfde = NULL;
        //     hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
        //     if (SUCCEEDED(hr))
        //     {
        //         // Hook up the event handler.
        //         DWORD dwCookie;
        //         hr = pfd->Advise(pfde, &dwCookie);
        //         if (SUCCEEDED(hr))
        //         {
        //             // Set the options on the dialog.
        //             DWORD dwFlags;
        //
        //             // Before setting, always get the options first in order
        //             // not to override existing options.
        //             hr = pfd->GetOptions(&dwFlags);
        //             if (SUCCEEDED(hr))
        //             {
        //                 // In this case, get shell items only for file system items.
        //                 hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
        //                 if (SUCCEEDED(hr))
        //                 {
        //                     // Set the file types to display only.
        //                     // Notice that this is a 1-based array.
        //                     hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
        //                     if (SUCCEEDED(hr))
        //                     {
        //                         // Set the selected file type index to Word Docs for this example.
        //                         hr = pfd->SetFileTypeIndex(INDEX_WORDDOC);
        //                         if (SUCCEEDED(hr))
        //                         {
        //                             // Set the default extension to be ".doc" file.
        //                             hr = pfd->SetDefaultExtension(L"doc;docx");
        //                             if (SUCCEEDED(hr))
        //                             {
        //                                 // Show the dialog
        //                                 hr = pfd->Show(NULL);
        //                                 if (SUCCEEDED(hr))
        //                                 {
        //                                     // Obtain the result once the user clicks
        //                                     // the 'Open' button.
        //                                     // The result is an IShellItem object.
        //                                     IShellItem* psiResult;
        //                                     hr = pfd->GetResult(&psiResult);
        //                                     if (SUCCEEDED(hr))
        //                                     {
        //                                         // We are just going to print out the
        //                                         // name of the file for sample sake.
        //                                         PWSTR pszFilePath = NULL;
        //                                         hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH,
        //                                             &pszFilePath);
        //                                         if (SUCCEEDED(hr))
        //                                         {
        //                                             TaskDialog(NULL,
        //                                                        NULL,
        //                                                        L"CommonFileDialogApp",
        //                                                        pszFilePath,
        //                                                        NULL,
        //                                                        TDCBF_OK_BUTTON,
        //                                                        TD_INFORMATION_ICON,
        //                                                        NULL);
        //                                             CoTaskMemFree(pszFilePath);
        //                                         }
        //                                         psiResult->Release();
        //                                     }
        //                                 }
        //                             }
        //                         }
        //                     }
        //                 }
        //             }
        //             // Unhook the event handler.
        //             pfd->Unadvise(dwCookie);
        //         }
        //         pfde->Release();
        //     }
        //     pfd->Release();
        // }
        //return hr;
    }
};
