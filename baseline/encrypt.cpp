#include "encrypt.h"

char* encrypt(char* plaintext, char* key){
    //generate the subkeys using the function defined above
    uint64_t* subkeys = generateSubkeys(key);
    //convert the plaintext from a Hex String to a 64-bit integer
    uint64_t state = fromHexStringToLong(plaintext);
    int i, j;
    //apply first 31 rounds
    for (i=0; i < 31; i++){
        //XOR the state with the round subkey
        state = state ^ subkeys[i];

        //run each nibble through the SBox
        uint64_t mask = 15;
        uint8_t sin, sres;
        for (j=0; j<16; j++) {
            sin = (state >> (4*j)) & mask;
            sres = Sbox(sin);
            state &= ~(mask << (4*j)); // clear the old nibble
            state |= (uint64_t)sres << (4*j);
        }
        //return the nibbles in a 64-bit integer format and perform the permutation defined above
        state = permute(state);
    }
    //the last round only XORs the state with the round key
    state = state ^ subkeys[31];
    //free the memory of the subkeys (they are not needed anymore)
    // free(subkeys);
    return fromLongToHexString(state);
}