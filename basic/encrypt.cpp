#include "encrypt.h"

void encrypt(ap_uint<128> key, ap_uint<64> *plaintext){
	ap_uint<64> state = *plaintext;
	ap_uint<64> tmp;
	ap_uint<128> tmp0 = key, tmp1, tmp2;
	ap_uint<4> S[] = {0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2};
	ap_uint<6> P[] = {0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,
	                    4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,
	                    8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,
	                    12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63};
    for(ap_uint<6> i = 0; i < 31; i++){
    	// cipher
        state = state ^ tmp0.range(127, 64);
        for(int j = 0; j < 16; j++){
        	state.range(j * 4 + 3, j * 4) = S[state.range(j * 4 + 3, j * 4)];
        }
        for(int j = 0; j < 64; j++){
            tmp[P[j]] = state[j];
        }
        state = tmp;

        // key schedule
        tmp1 = (tmp0.range(66, 0), tmp0.range(127, 67));
        tmp1.range(127, 124) = S[tmp1.range(127, 124)];
        tmp1.range(123, 120) = S[tmp1.range(123, 120)];
        tmp1.range(66, 62) = tmp1.range(66, 62) ^ (i + 1).range(4, 0);
        tmp0 = tmp1;
    }
    state = state ^ tmp0.range(127, 64);
    *plaintext = state;
}

