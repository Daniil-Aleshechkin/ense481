#include "main.h"
#include "sttimer.h"
#include "util.h"

#define RUNS 50

int main(void) {
    uint16_t volatile time = 0;
    uint16_t volatile startTime = 0;
    uint16_t volatile totalTimes[RUNS]; 

    // Initialize all testing variables
    int32_t testInt32s[RUNS];
    int64_t testInt64s[RUNS];
    struct byte_8* testByte8[RUNS];
    struct byte_128* testByte128[RUNS];
    struct byte_1024* testByte1024[RUNS];
    
    getRandomInt32s((int32_t*)&testInt32s, RUNS);
    getRandomInt64s((int64_t*)&testInt64s, RUNS);
    getRandomByte8s((struct byte_8**)&testByte8, RUNS);
    getRandomByte128s((struct byte_128**)&testByte128, RUNS);
    getRandomByte1024s((struct byte_1024**)&testByte1024, RUNS);

    timer_init();
    
    while(1) {
        startTime = timer_start();
        time = timer_stop(startTime);
    }
}
