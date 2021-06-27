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

void encrypt(ap_uint<128> *key, ap_uint<64> *plaintext){
	ap_uint<16> r[4];
	ap_uint<16> tmp0, tmp1, tmp2;
	ap_uint<16> t0 = 0;
	ap_uint<32> k[4], temp0[4];

	for(ap_uint<8> i = 0; i < 136; i++){
		if(!i.range(7, 3)){
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				k[j] >>= 4;
				k[j].range(31, 28) = (*key).range(127 - j * 4, 124 - j * 4);
			}
			(*key) <<= 16;
			if(!i[2]){
				for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
					r[j] >>= 4;
					r[j].range(15, 12) = (*plaintext).range(63 - j * 4, 60 - j * 4);
				}
				(*plaintext) <<= 16;
			}
		}else{
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				t0.range(j * 4 + 3, j * 4) = k[j].range(31, 28);
			}
			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
				k[j].range(31, 16) = (k[j].range(27, 16), k[j].range(31, 28));
			}
			if(i.range(1, 0) == 3){
				for(int j = 0; j < 128; j++){
#pragma HLS unroll factor=128
					int u = (j + 67) % 128;
					temp0[(j / 4) % 4][(j / 16) * 4 + j % 4] = k[(u / 4) % 4][(u / 16) * 4 + u % 4];
				}
				temp0[2].range(31, 28) = sbox(temp0[2].range(31, 28));
				temp0[3].range(31, 28) = sbox(temp0[3].range(31, 28));
				temp0[3].range(15, 14) = temp0[3].range(15, 14) ^ ((i - 4).range(3, 2));
				temp0[0].range(18, 16) = temp0[0].range(18, 16) ^ ((i - 4).range(6, 4));

				for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
					k[j] = temp0[j];
				}
			}

			if(!i[2]){
				for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
					tmp0.range(j * 4 + 3, j * 4) = r[3 - j].range(3, 0);
					r[3 - j] >>= 4;
				}
			}else{
				for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
					tmp0.range((3 - j) * 4 + 3, (3 - j) * 4) = r[0].range(j * 4 + 3, j * 4);
				}
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
			if(!i[2]){
				for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
					for(int u = 0; u < 4; u++){
#pragma HLS unroll factor=4
						r[3 - u][j + 12] = tmp2[j * 4 + u];
					}
				}
			}else{
				for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
					for(int u = 0; u < 4; u++){
#pragma HLS unroll factor=4
						r[3][(3 - u) * 4 + j] = tmp2[j * 4 + u];
					}
				}
			}
			*plaintext <<= 16;
			(*plaintext).range(15, 0) = tmp1;
		}
	}
}
