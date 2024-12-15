#pragma once

class WorkerRC4 {
    BYTE K[32] = {};
    BYTE S[256] = {};
    int i = 0;
    int j = 0;

    BYTE getNext() {
        i = i + 1 & 0xFF;
        j = j + S[i] & 0xFF;
        const auto temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        return S[S[i] + S[j] & 0xFF];
    }

public:
    void initKey(PCBYTE pKey, DWORD size) {
        i = j = 0;
        for (int x = 0; x < 32; x++) {
            K[x] = x * 8;
        }
        for (int x = 0; x < 256; x++) {
            S[x] = x;
        }
        if (size > 32) {
            for (int x = 0; x < size; x++) {
                K[x % 32] ^= pKey[x];
            }
        } else {
            for (int x = 0; x < 32; x++) {
                K[x] ^= pKey[x % size];
            }
        }
        for (int x = 0, y = 0; x < 256; x++) {
            y = y + S[x] + K[x % 32] & 0xFF;
            const auto temp = S[x];
            S[x] = S[y];
            S[y] = temp;
        }
        for (int x = 0; x < 256; x++) {
            getNext();
        }
    }

    void encryptHead(PBYTE pData, DWORD size) {
        for (int x = 0; x < size; x++) {
            pData[x] = getNext();
        }
    }

    void encryptData(PBYTE pData, DWORD size) {
        for (int x = 0; x < size; x++) {
            pData[x] ^= getNext();
        }
    }
};
