#include "stdint.h"

#ifndef UTIL
#define UTIL


struct byte_8 {
    int8_t bytes[8];
};

struct byte_128 {
    int8_t bytes[128];
};

struct byte_1024 {
    int8_t bytes[1024];
};


void getRandomInt32s(int32_t* ints, int8_t amount);
void getRandomInt64s(int64_t* ints, int8_t amount);
void getRandomByte8s(struct byte_8** byte8s, int8_t amount);
void getRandomByte128s(struct byte_128** byte8s, int8_t amount);
void getRandomByte1024s(struct byte_1024** byte8s, int8_t amount);

#endif