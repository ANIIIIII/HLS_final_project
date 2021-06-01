#include <iostream>
#include <cstdlib>
#include "encrypt.h"

using namespace std;


ap_uint<64> fromHexStringToLong (char block[]){
	ap_uint<64> result;
    // each character is 4 bits, there are 16 characters in a 64-bit block

    for (int i=0; i<16; i++)
        result = (result << 4) | ((block[i]>='0' && block[i]<='9')? (block[i] - '0') : (block[i] - 'a' + 10));
    return result;
}

void fromLongToHexString (ap_uint<64> block, char hexString[]){
	ap_uint<64> mask = 15;

    for (int i = 15; i >= 0; i--) {
    	ap_uint<8> tmp = (ap_uint<8>) (block & mask);

        if (tmp < 10) {
            hexString[i] = tmp + '0';
        } else {
            hexString[i] = tmp - 10 + 'a';
        }
        block >>= 4;
    }
    hexString[16] = '\0';

}


int main() {
	char plaintext[16 + 1] = "68656c6c6f030303", key[32 + 1] = "00000000000000000000000000000000";
    cout << "plaintext = 0x"<< plaintext << "\n";
    cout << "key = 0x" << key << "\n";

    // Encrypt
    ap_uint<64> state = 0x68656c6c6f030303;
    char res[32];
    encrypt(plaintext, key, &state);
    fromLongToHexString(state, res);
    cout << "ciphertext = 0x" << res << '\n';

    return 0;
}

