#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <iostream>
#include <cstdint>
using namespace std;

uint8_t Sbox(uint8_t);
uint64_t permute(uint64_t);
uint64_t fromHexStringToLong (char*);
char* fromLongToHexString(uint64_t);
uint64_t* generateSubkeys(char*);

#endif