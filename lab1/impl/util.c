#include "util.h"
#include <stdlib.h>

#define SEED 69

void getRandomInt32s(int32_t* ints, int8_t amount) {
    srand(SEED);
    ints = (int32_t*)malloc(sizeof(int32_t) * amount);


    for (int8_t i = 0; i < amount; i++) {
        ints[i] = (int32_t)(rand() & 0xFFFFFFFF);
    }
}


void getRandomInt64s(int64_t* ints, int8_t amount) {
    srand(SEED);
    ints = (int64_t*)malloc(sizeof(int64_t) * amount);


    for (int8_t i = 0; i < amount; i++) {
        ints[i] = (int64_t)(rand() & 0xFFFFFFFFFFFFFFFF);
    }
}

struct byte_8* allocByte8() {
    srand(SEED);
    struct byte_8* bytes = (struct byte_8*)malloc(sizeof(struct byte_8));

    for (int8_t i = 0; i < 8; i++) {
        bytes->bytes[i] = (int8_t)(rand() & 0xFF);
    }

    return bytes;

}

struct byte_128* allocByte128() {
    srand(SEED);
    struct byte_128* bytes = (struct byte_128*)malloc(sizeof(struct byte_128));

    for (int8_t i = 0; i < 128; i++) {
        bytes->bytes[i] = (int8_t)(rand() & 0xFF);
    }

    return bytes;
}

struct byte_1024* allocByte1024() {
    srand(SEED);
    struct byte_1024* bytes = (struct byte_1024*)malloc(sizeof(struct byte_1024));

    for (int8_t i = 0; i < 1024; i++) {
        bytes->bytes[i] = (int8_t)(rand() & 0xFF);
    }

    return bytes;
}