#include "functions.h"

// define the SBox
uint8_t S[] = {0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2};

// define the permutation table
uint8_t P[] = {0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,
                    4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,
                    8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,
                    12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};

uint8_t Sbox(uint8_t input) {
    return S[input];
}

uint64_t permute(uint64_t source){
    uint64_t permutation = 0;
    int i;
    for (i=0; i<64; i++){
        int distance = 63 - i;
        permutation = permutation | (((source >> distance) & 0x1) << 63 - P[i]);
    }
    return permutation;
}

uint64_t fromHexStringToLong (char* block){
    uint64_t result;
    int i;
    // each character is 4 bits, there are 16 characters in a 64-bit block
  
    for (i=0; i<16; i++)
        result = (result << 4) | ((block[i]>='0' && block[i]<='9')? (block[i] - '0') : (block[i] - 'a' + 10));
    return result;
}

char* fromLongToHexString (uint64_t block){
    static char hexString[17];
    uint64_t mask = 15;
    
    for (int i = 15; i >= 0; i--) {
        uint8_t tmp = (uint8_t) (block & mask);

        if (tmp < 10) {
            hexString[i] = tmp + '0';
        } else {
            hexString[i] = tmp - 10 + 'a';
        }
        block >>= 4;
    }
    hexString[16] = '\0';

    return hexString;
}

uint64_t* generateSubkeys(char* key) {
    uint64_t keyHigh = fromHexStringToLong(key);
    uint64_t keyLow = fromHexStringToLong(key + 16);
    // allocate space for 32 rounds
    uint64_t* subKeys = new uint64_t(32);
    uint8_t i;

    //the first subkey is the high part of the original key
    subKeys[0] = keyHigh;
    for (i=1; i<32; i++) {
        uint64_t temp1 = keyHigh, temp2 = keyLow;

        keyHigh = (keyLow >> 3) | (keyHigh << 61);
        keyLow = (keyLow << 61) | (keyHigh >> 3);
        //the most 2 significant nibbles of the key go through the SBox
        uint8_t s1 = Sbox(keyHigh >> 60);
        uint8_t s2 = Sbox((keyHigh << 4) >> 60);
        //the old value of the most significant nibble is set to zero using masking
        keyHigh = keyHigh & 0x00FFFFFFFFFFFFFFLL;
        //new most 2 significant nibbles (output of the SBox) are placed on the most significant location
        keyHigh = keyHigh | (((uint64_t)s1) << 60) |  (((uint64_t)s2) << 56);
        //key bits on positions k66, k65, k64, k63 and k62 XORed with round counter
        keyLow = keyLow ^ ((uint64_t) (i & 0x11) << 62);
        keyHigh = keyHigh ^ (i & 0x11100);
        //according to the key scheduling algorithm, the values of keyHigh are used as 64-bit subkeys
        subKeys[i] = keyHigh;
    }
    return subKeys;
}