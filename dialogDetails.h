#pragma once

#include "resource.h"

class DialogDetails {
    HWND hDialog = nullptr;
    HWND hDetails = nullptr;

    void addColumn(int index, int width, PCWSTR title) {
        LVCOLUMNW info = {};
        info.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        info.cx = getPixelX(width);
        info.pszText = (PWSTR) title;
        info.iSubItem = index;
        SendMessageW(hDetails, LVM_INSERTCOLUMN, index, (LPARAM) &info);
    }

    int addItem(int index) {
        LVITEMW info = {};
        info.mask = LVIF_PARAM;
        info.iItem = index;
        info.lParam = index;
        return (int) SendMessageW(hDetails, LVM_INSERTITEM, 0, (LPARAM) &info);
    }

    int getOffset(int index) {
        LVFINDINFOW info = {};
        info.flags = LVFI_PARAM;
        info.lParam = index;
        return (int) SendMessageW(hDetails, LVM_FINDITEM, -1, (LPARAM) &info);
    }

    int getPixelX(int dlu) {
        RECT rect = {};
        rect.left = dlu;
        MapDialogRect(hDialog, &rect);
        return rect.left;
    }

    void setText(int offset, int subId, PCWSTR text) {
        LVITEMW info = {};
        info.mask = LVIF_TEXT;
        info.iItem = offset;
        info.iSubItem = subId;
        info.pszText = (PWSTR) text;
        SendMessageW(hDetails, LVM_SETITEMTEXT, offset, (LPARAM) &info);
    }

public:
    void messageInit(HWND hDlg) {
        hDialog = hDlg;
        hDetails = GetDlgItem(hDlg, ID_DETAILS);
        SendMessageW(hDetails, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        addColumn(0, 160, L"文件名");
        addColumn(1, 100, L"状态");
    }

    void removeItem(int index) {
        const auto offset = getOffset(index);
        SendMessageW(hDetails, LVM_DELETEITEM, offset, 0);
    }

    void updateItem(int index, PCWSTR column1, PCWSTR column2) {
        auto offset = getOffset(index);
        if (offset < 0) {
            offset = addItem(index);
        }
        setText(offset, 0, column1);
        setText(offset, 1, column2);
    }
};
