#include "encrypt.h"

// define the SBox
ap_uint<8> S[] = {0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2};

// define the permutation table
ap_uint<8> P[] = {0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,
                    4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,
                    8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,
                    12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};

ap_uint<8> Sbox(ap_uint<8> input) {
    return S[input];
}

ap_uint<64> permute(ap_uint<64> source){
	ap_uint<64> permutation = 0;
    for (int i=0; i<64; i++){
        int distance = 63 - i;
        permutation = permutation | (((source >> distance) & 0x1) << 63 - P[i]);
    }
    return permutation;
}


void generateSubkeys(char* key, ap_uint<64> subKeys[32]) {
	ap_uint<64> keyHigh = 0;
	ap_uint<64> keyLow = 0;
    // allocate space for 32 rounds

    //the first subkey is the high part of the original key
    subKeys[0] = keyHigh;
    for(ap_uint<64> i=1; i<32; i++){
    	//ap_uint<64> temp1 = keyHigh, temp2 = keyLow;
    	ap_uint<64> tmp;
        tmp = (keyLow >> 3) | (keyHigh << 61);
        keyLow = (keyLow << 61) | (keyHigh >> 3);
        keyHigh = tmp;
        //the most 2 significant nibbles of the key go through the SBox
        ap_uint<64> s1 = Sbox(keyHigh >> 60);
        ap_uint<64> s2 = Sbox((keyHigh >> 56) & 0xf);
        //the old value of the most significant nibble is set to zero using masking
        keyHigh = (keyHigh & 0x00FFFFFFFFFFFFFFUL);
        //new most 2 significant nibbles (output of the SBox) are placed on the most significant location
        keyHigh = keyHigh | (s1 << 60) |  (s2 << 56);
        //key bits on positions k66, k65, k64, k63 and k62 XORed with round counter
        //keyLow = keyLow ^ ((ap_uint<64>) (i & 0x11) << 62);
        keyLow = keyLow ^ (i << 62);
        //keyHigh = keyHigh ^ (i & 0x11100);
        keyHigh = keyHigh ^ (i >> 2);
        //according to the key scheduling algorithm, the values of keyHigh are used as 64-bit subkeys
        subKeys[i] = keyHigh;
    }
}

void encrypt(char* plaintext, char* key, ap_uint<64> *state){
    //generate the subkeys using the function defined above
	ap_uint<64> subkeys[32];
	generateSubkeys(key, subkeys);
    //convert the plaintext from a Hex String to a 64-bit integer
    //apply first 31 rounds
    for (int i=0; i < 31; i++){
        //XOR the state with the round subkey
        *state = *state ^ subkeys[i];

        //run each nibble through the SBox
        ap_uint<64> mask = 15;
        ap_uint<8> sin, sres;
        for (int j=0; j<16; j++) {
            sin = (*state >> (4*j)) & mask;
            sres = Sbox(sin);
            *state &= ~(mask << (4*j)); // clear the old nibble
            *state |= (ap_uint<64>)sres << (4*j);
        }
        //return the nibbles in a 64-bit integer format and perform the permutation defined above
        *state = permute(*state);
    }
    //the last round only XORs the state with the round key
    *state = *state ^ subkeys[31];
    //free the memory of the subkeys (they are not needed anymore)
    // free(subkeys);
    //fromLongToHexString(state, res);
}

