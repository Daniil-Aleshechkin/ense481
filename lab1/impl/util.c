#include "util.h"
#include <stdlib.h>

void getRandomInts(int32_t* ints, int8_t amount) {
    srand(69);
    ints = (int32_t*)malloc(sizeof(int32_t) * amount);


    for (int8_t i = 0; i < amount; i++) {
        ints[i] = rand() & 0xFFFFFFFF;
    }
}