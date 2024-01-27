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
struct byte_8* allocByte8();
struct byte_128* allocByte128();
struct byte_1024* allocByte1024();

#endif