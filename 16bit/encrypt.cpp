#include "encrypt.h"
#include <iostream>


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
	ap_uint<64> state = *plaintext;
	ap_uint<64> p = *plaintext;
	ap_uint<64> tmp;
	//ap_uint<128> tmp00, tmp1, tmp2;
	ap_uint<16> t0 = 0 ;
	ap_uint<16> tmp0 ;
	ap_uint<16> tmp1 ;
	ap_uint<16> tmp2 ;

	// state registers for 16 bits plaintext
	ap_uint<16> r[4]; //  |4 4 4 4|4 4 4 4|4 4 4 4|4 4 4 4|

	// keys

	ap_uint<64> ori_keys[32] = {
			0x0,
			0xcc00000000000000,
			0xc300000000000000,
			0x5b30000000000000,
			0x580c000000000001,
			0x656cc00000000001,
			0x6e60300000000001,
			0xb595b30000000001,
			0xbeb980c000000002,
			0x96d656cc00000002,
			0x9ffae60300000002,
			0x65b595b30000002,
			0x0f7feb980c000003,
			0xac196d656cc00003,
			0xa33dffae60300003,
			0xd6b065b595b30003,
			0xdf8cf7feb980c004,
			0x3b5ac196d656cc04,
			0x387e33dffae60304,
			0xeced6b065b595b34,
			0xe3e1f8cf7feb9809,
			0x6bb3b5ac196d6569,
			0xbb8f87e33dffae65,
			0x80aeced6b065b590,
			0xc1ee3e1f8cf7febf,
			0x2602bb3b5ac196d0,
			0xcb07b8f87e33dffc,
			0x34980aeced6b065d,
			0x8b2c1ee3e1f8cf78,
			0x54d2602bb3b5ac1e,
			0x4a2cb07b8f87e33a,
			0x97534980aeced6b7
	};

	ap_uint<16> s_keys[128] = {
		0x0, 0x0, 0x0, 0x0,
		0x0000, 0x0000, 0x0000, 0xcc00,
		0x0000, 0x0000, 0x0000, 0xc300,
		0x0000, 0x0000, 0x0000, 0x5b30,
		0x0001, 0x0000, 0x0000, 0x580c,
		0x0001, 0x0000, 0xc000, 0x656c,
		0x0001, 0x0000, 0x3000, 0x6e60,
		0x0001, 0x0000, 0xb300, 0xb595,
		0x0002, 0x0000, 0x80c0, 0xbeb9,
		0x0002, 0x0000, 0x56cc, 0x96d6,
		0x0002, 0x0000, 0xe603, 0x9ffa,
		0x0002, 0x3000, 0x595b, 0x065b,
		0x0003, 0x0c00, 0xeb98, 0x0f7f,
		0x0003, 0x6cc0, 0x6d65, 0xac19,
		0x0003, 0x6030, 0xffae, 0xa33d,
		0x0003, 0x95b3, 0x65b5, 0xd6b0,
		0xc004, 0xb980, 0xf7fe, 0xdf8c,
		0xcc04, 0xd656, 0xc196, 0x3b5a,
		0x0304, 0xfae6, 0x33df, 0x387e,
		0x5b34, 0x5b59, 0x6b06, 0xeced,
		0x9809, 0x7feb, 0xf8cf, 0xe3e1,
		0x6569, 0x196d, 0xb5ac, 0x6bb3,
		0xae65, 0x3dff, 0x87e3, 0xbb8f,
		0xb590, 0xb065, 0xced6, 0x80ae,
		0xfebf, 0x8cf7, 0x3e1f, 0xc1ee,
		0x96d0, 0x5ac1, 0xbb3b, 0x2602,
		0xdffc, 0x7e33, 0xb8f8, 0xcb07,
		0x065d, 0xed6b, 0x0aec, 0x3498,
		0xcf78, 0xe1f8, 0x1ee3, 0x8b2c,
		0xac1e, 0xb3b5, 0x602b, 0x54d2,
		0xe33a, 0x8f87, 0xb07b, 0x4a2c,
		0xd6b7, 0xaece, 0x4980, 0x9753
	};


    for(int i = 0; i < 4; i++){
#pragma HLS unroll factor=4
    	r[i].range(3,0) = p.range(i*4+3, i*4) ;
    	r[i].range(7,4) = p.range(i*4+16+3, i*4+16) ;
    	r[i].range(11,8) = p.range(i*4+32+3, i*4+32) ;
		r[i].range(15,12) = p.range(i*4+48+3, i*4+48) ;
    }


    for(int i = 0; i < 124; i++){
    // cipher
    	int index = i % 4;


    	if(i % 8 <= 3){
    		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
    			tmp0.range(j * 4 + 3, j * 4) = r[j].range(index*4+3, index*4+0);
    		}
    	}else{
    		tmp0 = r[index] ;
    	}

    	tmp1 = tmp0 ^ s_keys[i];

        // in 16-bit only 4
    	for(int j = 0; j < 4; j++){
#pragma HLS unroll factor = 4
    		tmp2.range(j * 4 + 3, j * 4) = sbox(tmp1.range(j * 4 + 3, j * 4));
        }



    	if(i % 8 <= 3){
    		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
    			for(int u = 0; u < 4; u++){
#pragma HLS unroll factor=4
    				r[u].range(index*4 + j, index * 4 + j) = tmp2.range(j * 4 + u, j * 4 + u);
    			}
    		}
    	}else{
    		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
    			for(int u = 0; u < 4; u++){
#pragma HLS unroll factor=4
    				r[index].range(u * 4 + j, u * 4 + j) = tmp2.range(j * 4 + u, j * 4 + u);
    			}
    		}
    	}


    }

    ap_uint<64> ans = 0 ;
    for( int i = 0 ; i < 4 ; i++){
#pragma HLS unroll factor=4
    	r[i] = r[i] ^ s_keys[124+i] ;
    	ans.range(i*16+15, i*16+0) = r[i] ;
    }

    //state = state ^ tmp0.range(127, 64);
    *plaintext = ans;

}