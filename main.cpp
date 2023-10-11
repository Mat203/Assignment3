#include <iostream>
#include <windows.h>
using namespace std;

typedef char* (__cdecl *encrypt)(char*, int);
typedef char* (__cdecl *decrypt)(char*, int);

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

    char* rawText = "Hello, World!";
    int key = 3;

    char* encryptedText = (*encrypt_ptr)(rawText, key);
    std::cout << "Encrypted text: " << encryptedText << std::endl;

    char* decryptedText = (*decrypt_ptr)(encryptedText, key);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    delete[] encryptedText;
    delete[] decryptedText;

    FreeLibrary(handle);

    return 0;
}
