#pragma once

class WorkerCrypto {
    //    HCRYPTPROV hCrypt = 0;
    //    HCRYPTHASH hHash = 0;
    //    HCRYPTKEY hKey = 0;
    //    BYTE bufferIV[16] = {};
    //
    //    int initContext() {
    //        return CryptAcquireContextW(&hCrypt, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    //    }
    //
    //    int initKey(const void *pKey, int size) {
    //        if (!CryptCreateHash(hCrypt, CALG_SHA1, 0, 0, &hHash)) {
    //            return 0;
    //        }
    //        if (!CryptHashData(hHash, (PBYTE) pKey, size, 0)) {
    //            return 0;
    //        }
    //        if (!CryptDeriveKey(hCrypt, CALG_AES_256, hHash, 0, &hKey)) {
    //            return 0;
    //        }
    //        return 1;
    //    }
    //
    //    int initIV(const void *pIV, int size) {
    //        if (size == 16) {
    //            memcpy(bufferIV, pIV, 16);
    //        } else {
    //
    //        }
    //        if (!CryptSetKeyParam(hKey, KP_IV, bufferIV, 0)) {
    //            return 0;
    //        }
    //        DWORD mode = CRYPT_MODE_OFB;
    //        if (!CryptSetKeyParam(hKey, KP_MODE, (PBYTE) &mode, 0)) {
    //            return 0;
    //        }
    //        return 1;
    //    }
    //
    //    void releaseCrypt() {
    //        if (hHash) {
    //            CryptDestroyHash(hHash);
    //            hHash = 0;
    //        }
    //        if (hKey) {
    //            CryptDestroyKey(hKey);
    //            hKey = 0;
    //        }
    //        if (hCrypt) {
    //            CryptReleaseContext(hCrypt, 0);
    //            hCrypt = 0;
    //        }
    //    }
    //
    //public:
    //    CoreRC4() {
    //        releaseCrypt();
    //    }
    //
    //    int initKey(PCSTR pKey) {
    //        releaseCrypt();
    //        if (!) {
    //            return 0;
    //        }
    //    }
    //
    //    int initSalt() {
    //        memset(buffer1, 0, 16);
    //        offset = 16;
    //        return CryptGenRandom(hCrypt, 12, buffer1);
    //    }
    //
    //    int initSalt(PBYTE pSalt) {
    //        memset(buffer1, 0, 16);
    //        memcpy_s(buffer1, 16, pSalt, 12);
    //        offset = 16;
    //        return 1;
    //    }
    //
    //    void encryptData(PBYTE pData, int size) {
    //        for (int i = 0; i < size; i++) {
    //            if (offset >= 16) {
    //                (*PDWORD(buffer1 + 12))++;
    //                memcpy_s(buffer2, 16, buffer1, 16);
    //                DWORD size2 = 16;
    //                CryptEncrypt(hKey, 0, 0, 0, buffer2, &size2, 16);
    //                offset = 0;
    //            }
    //            pData[i] ^= buffer2[offset++];
    //        }
    //    }
};
