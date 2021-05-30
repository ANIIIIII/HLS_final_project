#include <iostream>
#include "encrypt.h"
#include "functions.h"
using namespace std;

int main() {
    char plaintext[65], key[129];
    int now;

    cout << "plaintext = 0x";
    for (int i = 0; i < 64; i++) {
        now = (6*i*i + 9*i + 87) % 16;

        if (now < 10) {
            plaintext[i] = now + '0';
        } else {
            plaintext[i] = now - 10 + 'a';
        }
        cout << plaintext[i];
    }
    plaintext[64] = '\0';
    cout << '\n';

    cout << "key = 0x";
    for (int i = 0; i < 128; i++) {
        now = (5*i*i + 7*i + 8) % 16;

        if (now < 10) {
            key[i] = now + '0';
        } else {
            key[i] = now - 10 + 'a';
        }
        cout << key[i];
    }
    key[128] = '\0';
    cout << '\n';

    // Encrypt
    char* res;
    res = encrypt(plaintext, key);
    cout << "Result: 0x" << res << '\n';

    return 0;
}
