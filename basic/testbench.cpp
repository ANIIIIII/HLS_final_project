#include <iostream>
#include <cstdlib>
#include "encrypt.h"

using namespace std;

int main() {
	char plaintext[16 + 1] = "68656c6c6f030303", key[32 + 1] = "00000000000000000000000000000000";
    cout << "plaintext = 0x"<< plaintext << "\n";
    cout << "key = 0x" << key << "\n";

    // Encrypt
    char res[32];
    encrypt(plaintext, key, res);
    cout << "ciphertext = 0x" << res << '\n';

    return 0;
}

