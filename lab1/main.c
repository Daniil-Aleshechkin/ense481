#include "main.h"
#include "sttimer.h"

void delay(int millis) {
    while (millis-- > 0) {
        volatile int x = 2;
        while (x-- > 0) {
            __asm("nop");
        }
    }
}

int main(void) {

    // GPIO structure for port initialization
    GPIO_InitTypeDef GPIO_InitStructure;
    uint16_t time = 0;
    uint16_t startTime = 0;
    // enable clock on APB2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);

    // configure port A1 for driving an LED
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // output push-pull mode
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // highest speed
    GPIO_Init(GPIOA, &GPIO_InitStructure) ;             // initialize port

    timer_init();

    // main loop
    while(1) {
        startTime = timer_start();
        GPIO_SetBits(GPIOA, GPIO_Pin_5);    // turn the LED on
        delay(DELAY);

        GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // turn the LED off
        delay(DELAY);
        time = timer_stop(startTime);
    }
}
