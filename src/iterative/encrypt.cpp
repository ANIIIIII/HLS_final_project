#include "encrypt.h"

ap_uint<4> sbox(ap_uint<4> out){
	switch(out){
	case 0: out = 0xc; break;
	case 1: out = 0x5; break;
	case 2: out = 0x6; break;
	case 3: out = 0xb; break;
	case 4: out = 0x9; break;
	case 5: out = 0x0; break;
	case 6: out = 0xa; break;
	case 7: out = 0xd; break;
	case 8: out = 0x3; break;
	case 9: out = 0xe; break;
	case 10: out = 0xf; break;
	case 11: out = 0x8; break;
	case 12: out = 0x4; break;
	case 13: out = 0x7; break;
	case 14: out = 0x1; break;
	case 15: out = 0x2; break;
	}
	return out;
}

ap_uint<6> permutation(ap_uint<6> out){
	switch(out){
	case 0: out = 0; break;
	case 1: out = 16; break;
	case 2: out = 32; break;
	case 3: out = 48; break;
	case 4: out = 1; break;
	case 5: out = 17; break;
	case 6: out = 33; break;
	case 7: out = 49; break;
	case 8: out = 2; break;
	case 9: out = 18; break;
	case 10: out = 34; break;
	case 11: out = 50; break;
	case 12: out = 3; break;
	case 13: out = 19; break;
	case 14: out = 35; break;
	case 15: out = 51; break;
	case 16: out = 4; break;
	case 17: out = 20; break;
	case 18: out = 36; break;
	case 19: out = 52; break;
	case 20: out = 5; break;
	case 21: out = 21; break;
	case 22: out = 37; break;
	case 23: out = 53; break;
	case 24: out = 6; break;
	case 25: out = 22; break;
	case 26: out = 38; break;
	case 27: out = 54; break;
	case 28: out = 7; break;
	case 29: out = 23; break;
	case 30: out = 39; break;
	case 31: out = 55; break;
	case 32: out = 8; break;
	case 33: out = 24; break;
	case 34: out = 40; break;
	case 35: out = 56; break;
	case 36: out = 9; break;
	case 37: out = 25; break;
	case 38: out = 41; break;
	case 39: out = 57; break;
	case 40: out = 10; break;
	case 41: out = 26; break;
	case 42: out = 42; break;
	case 43: out = 58; break;
	case 44: out = 11; break;
	case 45: out = 27; break;
	case 46: out = 43; break;
	case 47: out = 59; break;
	case 48: out = 12; break;
	case 49: out = 28; break;
	case 50: out = 44; break;
	case 51: out = 60; break;
	case 52: out = 13; break;
	case 53: out = 29; break;
	case 54: out = 45; break;
	case 55: out = 61; break;
	case 56: out = 14; break;
	case 57: out = 30; break;
	case 58: out = 46; break;
	case 59: out = 62; break;
	case 60: out = 15; break;
	case 61: out = 31; break;
	case 62: out = 47; break;
	case 63: out = 63; break;
	}
	return out;
}

void encrypt(ap_uint<128> key, ap_uint<64> *plaintext){
	static ap_uint<4> cnt; // 4-bit counter
	static ap_uint<6> round; // 6-bit round counter

	static ap_uint<64> state;
	static ap_uint<128> key_state = key;
	ap_uint<64> cipher_wire1, cipher_wire2;
	ap_uint<128> key_wire;

    // read input through 8-bit I/O 
    INPUT: for (cnt = 0; cnt < 8; cnt++) {
        state.range(63-8*cnt, 56-8*cnt) = plaintext->range(63-8*cnt, 56-8*cnt) ^ key_state.range(127-8*cnt, 120-8*cnt);
    }

    // encrypt for 31 rounds
    ENCODE: for(round = 0; round < 31; round++) {
        // s-box
        for(ap_uint<5> j = 0; j < 16; j++) {
#pragma HLS unroll factor = 16
        	cipher_wire1.range((j+1)*4-1, j*4) = sbox(state.range((j+1)*4-1, j*4));
        }
        // permutation
        for(ap_uint<7> j = 0; j < 64; j++){
#pragma HLS unroll factor = 64
            cipher_wire2[permutation(j)] = cipher_wire1[j];
        }

        // key scheduling
        key_wire = (key_state.range(66, 0), key_state.range(127, 67));
        key_wire.range(127, 124) = sbox(key_wire.range(127, 124));
        key_wire.range(123, 120) = sbox(key_wire.range(123, 120));
        key_wire.range(66, 62) = key_wire.range(66, 62) ^ (round + 1).range(4, 0);

        state = cipher_wire2 ^ key_wire.range(127, 64); // xor key
        key_state = key_wire;
    }

    // output through 8-bit I/O
    OUTPUT: for (cnt = 0; cnt < 8; cnt++) {
        plaintext->range(63-8*cnt, 56-8*cnt) = state.range(63-8*cnt, 56-8*cnt);
    }
}
