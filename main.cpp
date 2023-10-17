#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>
using namespace std;

typedef char* (__cdecl *encrypt)(char*, int);
typedef char* (__cdecl *decrypt)(char*, int);

std::string to_hex(char* input) {
    std::string result;
    char buffer[3];
    for (size_t i = 1; i < strlen(input); ++i) {
        sprintf(buffer, "%02x", static_cast<unsigned char>(input[i]));
        result.append(buffer);
    }
    return result;
}

int main() {
    HINSTANCE handle = LoadLibrary(TEXT("library.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Lib not found" << std::endl;
        return 1;
    }

    encrypt encrypt_ptr = (encrypt)GetProcAddress(handle, TEXT("encrypt"));
    if (encrypt_ptr == nullptr)
    {
        std::cout << "Function not found" << std::endl;
        return 1;
    }

    decrypt decrypt_ptr = (decrypt)GetProcAddress(handle, TEXT("decrypt"));
    if (decrypt_ptr == nullptr)
    {
        std::cout << "Function not found" << std::endl;
        return 1;
    }

    string inputText;
    int key;

    cout << "Enter the text to be encrypted: ";
    std::getline(std::cin, inputText);

    cout << "Enter the key: ";
    cin >> key;

    char* rawText = new char[inputText.length() + 1];
    strcpy(rawText, inputText.c_str());

    char* encryptedText = (*encrypt_ptr)(rawText, key);
    std::string hexText = to_hex(encryptedText);
    std::cout << "Encrypted text: " << hexText << std::endl;

    char* decryptedText = (*decrypt_ptr)(encryptedText, key);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    delete[] rawText;
    delete[] encryptedText;
    delete[] decryptedText;

    FreeLibrary(handle);

    return 0;
}
