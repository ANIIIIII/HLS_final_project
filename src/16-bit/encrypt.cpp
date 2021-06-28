#include "encrypt.h"


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


ap_uint<16> Skeys(ap_uint<16> out){
#pragma HLS inline
	switch(out){
	case 0: out = 0x0; break;
	case 1: out = 0x0; break;
	case 2: out = 0x0; break;
	case 3: out = 0x0; break;
	case 4: out = 0x0; break;
	case 5: out = 0x0; break;
	case 6: out = 0x0; break;
	case 7: out = 0x0; break;
	case 8: out = 0x0000; break;
	case 9: out = 0x0000; break;
	case 10: out = 0x0000; break;
	case 11: out = 0xcc00; break;
	case 12: out = 0x0000; break;
	case 13: out = 0x0000; break;
	case 14: out = 0x0000; break;
	case 15: out = 0xc300; break;
	case 16: out = 0x0000; break;
	case 17: out = 0x0000; break;
	case 18: out = 0x0000; break;
	case 19: out = 0x5b30; break;
	case 20: out = 0x0001; break;
	case 21: out = 0x0000; break;
	case 22: out = 0x0000; break;
	case 23: out = 0x580c; break;
	case 24: out = 0x0001; break;
	case 25: out = 0x0000; break;
	case 26: out = 0xc000; break;
	case 27: out = 0x656c; break;
	case 28: out = 0x0001; break;
	case 29: out = 0x0000; break;
	case 30: out = 0x3000; break;
	case 31: out = 0x6e60; break;
	case 32: out = 0x0001; break;
	case 33: out = 0x0000; break;
	case 34: out = 0xb300; break;
	case 35: out = 0xb595; break;
	case 36: out = 0x0002; break;
	case 37: out = 0x0000; break;
	case 38: out = 0x80c0; break;
	case 39: out = 0xbeb9; break;
	case 40: out = 0x0002; break;
	case 41: out = 0x0000; break;
	case 42: out = 0x56cc; break;
	case 43: out = 0x96d6; break;
	case 44: out = 0x0002; break;
	case 45: out = 0x0000; break;
	case 46: out = 0xe603; break;
	case 47: out = 0x9ffa; break;
	case 48: out = 0x0002; break;
	case 49: out = 0x3000; break;
	case 50: out = 0x595b; break;
	case 51: out = 0x065b; break;
	case 52: out = 0x0003; break;
	case 53: out = 0x0c00; break;
	case 54: out = 0xeb98; break;
	case 55: out = 0x0f7f ; break;
	case 56: out = 0x0003; break;
	case 57: out = 0x6cc0; break;
	case 58: out = 0x6d65; break;
	case 59: out = 0xac19; break;
	case 60: out = 0x0003; break;
	case 61: out = 0x6030; break;
	case 62: out = 0xffae; break;
	case 63: out = 0xa33d; break;
	case 64: out = 0x0003; break;
	case 65: out = 0x95b3; break;
	case 66: out = 0x65b5; break;
	case 67: out = 0xd6b0; break;
	case 68: out = 0xc004; break;
	case 69: out = 0xb980; break;
	case 70: out = 0xf7fe; break;
	case 71: out = 0xdf8c; break;
	case 72: out = 0xcc04; break;
	case 73: out = 0xd656; break;
	case 74: out = 0xc196; break;
	case 75: out = 0x3b5a; break;
	case 76: out = 0x0304; break;
	case 77: out = 0xfae6; break;
	case 78: out = 0x33df; break;
	case 79: out = 0x387e; break;
	case 80: out = 0x5b34; break;
	case 81: out = 0x5b59; break;
	case 82: out = 0x6b06; break;
	case 83: out = 0xeced; break;
	case 84: out = 0x9809; break;
	case 85: out = 0x7feb; break;
	case 86: out = 0xf8cf; break;
	case 87: out = 0xe3e1; break;
	case 88: out = 0x6569; break;
	case 89: out = 0x196d; break;
	case 90: out = 0xb5ac; break;
	case 91: out = 0x6bb3; break;
	case 92: out = 0xae65; break;
	case 93: out = 0x3dff; break;
	case 94: out = 0x87e3; break;
	case 95: out = 0xbb8f; break;
	case 96: out = 0xb590; break;
	case 97: out = 0xb065; break;
	case 98: out = 0xced6; break;
	case 99: out = 0x80ae; break;
	case 100: out = 0xfebf; break;
	case 101: out = 0x8cf7; break;
	case 102: out = 0x3e1f; break;
	case 103: out = 0xc1ee; break;
	case 104: out = 0x96d0; break;
	case 105: out = 0x5ac1; break;
	case 106: out = 0xbb3b; break;
	case 107: out = 0x2602; break;
	case 108: out = 0xdffc; break;
	case 109: out = 0x7e33; break;
	case 110: out = 0xb8f8; break;
	case 111: out = 0xcb07; break;
	case 112: out = 0x065d; break;
	case 113: out = 0xed6b; break;
	case 114: out = 0x0aec; break;
	case 115: out = 0x3498; break;
	case 116: out = 0xcf78; break;
	case 117: out = 0xe1f8; break;
	case 118: out = 0x1ee3; break;
	case 119: out = 0x8b2c; break;
	case 120: out = 0xac1e; break;
	case 121: out = 0xb3b5; break;
	case 122: out = 0x602b; break;
	case 123: out = 0x54d2; break;
	case 124: out = 0xe33a; break;
	case 125: out = 0x8f87; break;
	case 126: out = 0xb07b; break;
	case 127: out = 0x4a2c; break;
	case 128: out = 0xd6b7; break;
	case 129: out = 0xaece; break;
	case 130: out = 0x4980; break;
	case 131: out = 0x9753; break;
	}
	return out;
}


void encrypt(ap_uint<128> *key, ap_uint<64> *plaintext){
	ap_uint<64> tmp;
	ap_uint<16> t0 = 0 ;
	ap_uint<16> tmp0 ;
	ap_uint<16> tmp1 ;
	ap_uint<16> tmp2 ;

	// state registers for 16 bits plaintext
	ap_uint<16> r[4]; //  |4 4 4 4|4 4 4 4|4 4 4 4|4 4 4 4|


    for(ap_uint<8> i = 0; i < 132; i++){
    // cipher
    	if(!i.range(7, 2)){
    		for(int j = 0 ; j < 4; j++){
#pragma HLS unroll factor=4
    			r[i].range(3+j*4, j*4) = (*plaintext).range(3+j*16, j*16);
    		 }
    		(*plaintext) >>= 4;
    	}else{
    		if( i.range(7,7) ){
    			(*plaintext) >>= 16 ;
    			(*plaintext).range(63, 48) = r[i-128] ^ Skeys(i) ;
    		}
    		int index = (i-4) % 4;
    		if(!(i-4)[2]){
    			for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
    		    	tmp0.range(j * 4 + 3, j * 4) = r[j].range(index*4+3, index*4+0);
    		    }
    		 }else{
    		    	tmp0 = r[index] ;
    		 }

    		tmp1 = tmp0 ^ Skeys(i) ;

    		 // in 16-bit only 4
    		for(int j = 0; j < 4; j++){
#pragma HLS unroll factor=4
    		    tmp2.range(j * 4 + 3, j * 4) = sbox(tmp1.range(j * 4 + 3, j * 4));
    		}

    		if(!(i-4)[2]){
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
    }
}