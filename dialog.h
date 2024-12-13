#pragma once

#include "dialogDetails.h"
#include "dialogExplorer.h"
#include "dialogPassword.h"
#include "dialogMaster.h"

class Dialog {
    DialogDetails details = {};
    DialogExplorer explorer = {};
    DialogMaster master = {};
    DialogPassword password = {};

    void messageCommand(WPARAM wParam) {
        switch (wParam) {
            case ID_CLEAR:
                commandClear();
                break;
            case ID_DECRYPT:
            case ID_ENCRYPT:
                commandEncrypt(wParam);
                break;
            default:;
        }
    }

    void messageUpdate(LPARAM lParam) {
        const auto worker = (DialogWorker *) lParam;
        details.updateItem(worker->index, worker->column1, worker->column2);
    }

    void commandClear() {
        while (const auto worker = master.removeClose()) {
            details.removeItem(worker->index);
            delete worker;
        }
    }

    void commandEncrypt(WPARAM wParam) {
        if (!password.openPassword()) {
            return;
        }
        if (!explorer.openExplorer()) {
            return;
        }
        const auto key = password.getKey();
        while (const auto file = explorer.getFile()) {
            if (wParam == ID_ENCRYPT) {
                master.newEncrypt(file, key);
            } else {
                master.newDecrypt(file, key);
            }
        }
    }

public:
    INT_PTR messageMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case APP_UPDATE:
                messageUpdate(lParam);
                return 1;
            case WM_CLOSE:
                EndDialog(hDlg, 0);
                return 1;
            case WM_COMMAND:
                password.messageCommand(wParam);
                messageCommand(wParam);
                return 1;
            case WM_INITDIALOG:
                details.messageInit(hDlg);
                explorer.messageInit(hDlg);
                master.messageInit(hDlg);
                password.messageInit(hDlg);
                return 1;
            default:
                return 0;
        }
    }
};
