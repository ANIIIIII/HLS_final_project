#include <iostream>
#include <cstdlib>
#include "encrypt.h"

using namespace std;

int main() {
    ap_uint<64> state = 0x68656c6c6f030303;
    ap_uint<128> key = 0;
    cout << "plaintext = " << hex << state << "\n";
    cout << "key = 0x" << key << "\n";
    encrypt(key, &state);
    cout << "ciphertext = " << hex << state << '\n';

    return 0;
}

