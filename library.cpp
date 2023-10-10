#include "pch.h"
#include <iostream>
#include <cstring>

extern "C" {
    __declspec(dllexport) char* encrypt(char* rawText, int key) {
        int length = strlen(rawText);
        char* encryptedText = new char[length + 1];

        for (int i = 0; i < length; i++) {
            char c = rawText[i];

            if (isalpha(c)) {
                if (islower(c)) {
                    c = c + key;
                    if (c > 'z') {
                        c = c - 26;
                    }
                    else if (c < 'a') {
                        c = c + 26;
                    }
                }
                else {
                    c = c + key;
                    if (c > 'Z') {
                        c = c - 26;
                    }
                    else if (c < 'A') {
                        c = c + 26;
                    }
                }
            }
            encryptedText[i] = c;
        }

        encryptedText[length] = '\0';
        return encryptedText;
    }

    __declspec(dllexport) char* decrypt(char* encryptedText, int key) {
        int length = strlen(encryptedText);
        char* decryptedText = new char[length + 1];

        for (int i = 0; i < length; i++) {
            char c = encryptedText[i];

            if (isalpha(c)) {
                if (islower(c)) {
                    c = c - key;
                    if (c < 'a') {
                        c = c + 26;
                    }
                    else if (c > 'z') {
                        c = c - 26;
                    }
                }
                else {
                    c = c - key;
                    if (c < 'A') {
                        c = c + 26;
                    }
                    else if (c > 'Z') {
                        c = c - 26;
                    }
                }
            }
            decryptedText[i] = c;
        }

        decryptedText[length] = '\0';
        return decryptedText;
    }
}