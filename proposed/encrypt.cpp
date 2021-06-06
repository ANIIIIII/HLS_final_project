#include "encrypt.h"
#include  <iomanip>
ap_uint<4> sbox(ap_uint<4> out){
#pragma HLS inline
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
#pragma HLS inline
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
#pragma HLS expression_balance
	ap_uint<64> state = *plaintext;
	ap_uint<16> r[4];
	ap_uint<64> p = *plaintext;
	ap_uint<1> ctr_r = 0, ctr_k = 0;
	ap_uint<16> tmp0, tmp1, tmp2, tmp3;
	ap_uint<16> t0 = 0, t1, t2, t3;
	ap_uint<32> k[4], temp0[4], temp1[4];
	ap_uint<5> cnt = 1;
	// initialization
	for(int i = 0; i < 4; i++){
#pragma HLS unroll factor=4
		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
			r[j] >>= 4;
			r[j].range(15, 12) = p.range(i * 16 +  j * 4 + 3, i * 16 +  j * 4);
		}
	}
	for(int i = 0; i < 8; i++){
#pragma HLS unroll factor=8
		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
			k[j] >>= 4;
			k[j].range(31, 28) = key.range(i * 16 +  j * 4 + 3, i * 16 +  j * 4);
		}
	}

	for(int i = 1; i < 129; i++){

		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
			t0.range(j * 4 + 3, j * 4) = temp1[j].range((i % 4) * 4 + 16 + 3, (i % 4) * 4 + 16);
		}
		// key schedule
		if((i - 1) % 8 <= 3){
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				tmp0.range(j * 4 + 3, j * 4) = r[j].range(3, 0);
				r[j] >>= 4;
			}
		}else{
			tmp0 = r[0];
			r[0] = r[1];
			r[1] = r[2];
			r[2] = r[3];
		}


		// add round key
		tmp1 = tmp0 ^ t0;

		// sbox
		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
			tmp2.range(j * 4 + 3, j * 4) = sbox(tmp1.range(j * 4 + 3, j * 4));
		}

		// permutation
		if((i - 1) % 8 <= 3){
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				for(int u = 0; u < 4; u++){
#pragma HLS unroll factor=4
					r[u].range(j + 12, j + 12) = tmp2.range(j * 4 + u, j * 4 + u);
				}
			}
		}else{
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				for(int u = 0; u < 4; u++){
#pragma HLS unroll factor=4
					r[3].range(u * 4 + j, u * 4 + j) = tmp2.range(j * 4 + u, j * 4 + u);
				}
			}
		}


		// key
		if(i % 4 == 3){
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				k[j] = temp1[j];
			}
		}else if(i % 4 == 1){
			for(int j = 0; j < 128; j++){
#pragma HLS unroll factor=128
				int u = (j + 67) % 128;
				temp0[(j / 4) % 4][(j / 16) * 4 + j % 4] = k[(u / 4) % 4][(u / 16) * 4 + u % 4];
			}
		}else if(i % 4 == 2){
			temp1[2].range(31, 28) = sbox(temp0[2].range(31, 28));
			temp1[3].range(31, 28) = sbox(temp0[3].range(31, 28));
			temp1[3].range(15, 14) = temp0[3].range(15, 14) ^ cnt.range(1, 0);
			temp1[0].range(18, 16) = temp0[0].range(18, 16) ^ cnt.range(4, 2);
			cnt = cnt + 1;
		}

		state >>= 16;
		state.range(63, 48) = tmp1;
	}
	*plaintext = state;
}

