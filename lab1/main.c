#include "sttimer.h"
#include "time_ops.h"
#include "util.h"
#include "stdlib.h"
#include "CLI.h"
#include "LED.h"
#include <stdio.h>
#include <string.h>

#define RUNS 100

void testWithTimer(void);
void testAndPrintWithTimer(void);

#define COMMAND_STRING_BUFFER_SIZE 30

#define TURN_ON_STRING "turnon"
#define TURN_OFF_STRING "turnoff"
#define STATUS_STRING "status"
#define HELP_STRING "help"
#define TEST_TIMINGS_STRING "testtimes"

extern const char* USER_PROMPT;
const char* USER_PROMPT = "Enter a command (help displays a list): ";

extern const char* HELP_TEXT;
const char* HELP_TEXT = "Commands: \
												 Turnon: Turns on the LED \
												 Turnoff: Turns off the LED \
												 Help: Prints command list \
												 Status: Indicates LED status";

extern const char* LED_ON_STATUS_TEXT;
extern const char* LED_OFF_STATUS_TEXT;
const char* LED_ON_STATUS_TEXT  = "LED is ON";
const char* LED_OFF_STATUS_TEXT  = "LED is OFF";

extern const char* TURN_ON_LED_TEXT;
extern const char* TURN_OFF_LED_TEXT;
const char* TURN_ON_LED_TEXT = "LED turning on";
const char* TURN_OFF_LED_TEXT = "LED turning off";

extern const char* UNKNOWN_COMMAND_ERROR;
const char* UNKNOWN_COMMAND_ERROR = "Unknown command";

void processCommand(enum Commands command);
enum Commands readCommand(void);
enum Commands parseReturnCommand(char*);
void toLowerCase(char*);

void toLowerCase(char* str) {
    int i = 0;
    while (str[i] != 0x00) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

enum Commands parseReturnCommand(char* commandInput) {
	if(strcmp(TURN_ON_STRING, commandInput) == 0x00) {
		return TURN_ON;
	} else if (strcmp(TURN_OFF_STRING, commandInput) == 0x00) {
		return TURN_OFF;
	} else if (strcmp(HELP_STRING, commandInput) == 0x00) {
		return HELP;
	} else if (strcmp(STATUS_STRING, commandInput) == 0x00) {
		return STATUS;
	} else if (strcmp(TEST_TIMINGS_STRING, commandInput) == 0x00) {
		return TEST_TIMINGS;
	} else {
		return UNKNOWN;
	}
}

void processCommand(enum Commands command) {
	switch(command){
		case TURN_ON:
			printScreen((const uint8_t*)TURN_ON_LED_TEXT);
			turnOnLED();
			break;
		case TURN_OFF:
			printScreen((const uint8_t*)TURN_OFF_LED_TEXT);
			turnOffLED();
			break;
		case HELP:
			printScreen((const uint8_t*)HELP_TEXT);
			break;
		case STATUS:
			if (getLEDStatus()) {
				printScreen((const uint8_t*)LED_ON_STATUS_TEXT);
			} else {
				printScreen((const uint8_t*)LED_OFF_STATUS_TEXT);
			}
			break;
		case TEST_TIMINGS:
			testAndPrintWithTimer();
			break;
		case UNKNOWN:
			printScreen((const uint8_t*)UNKNOWN_COMMAND_ERROR);
			break;
		
	}
}

enum Commands readCommand() {
	char (*commandStrBuffer)[COMMAND_STRING_BUFFER_SIZE];
	enum Commands returnCommand;
	
	commandStrBuffer = (char(*)[COMMAND_STRING_BUFFER_SIZE])malloc(COMMAND_STRING_BUFFER_SIZE * sizeof(char));
	
	toLowerCase((char*)commandStrBuffer);
	
	CLI_Receive((uint8_t*)commandStrBuffer, COMMAND_STRING_BUFFER_SIZE);
	
	returnCommand = parseReturnCommand((char*)commandStrBuffer);
	
	free(commandStrBuffer);
	
	return returnCommand;
}


//static int32_t testInt32s[RUNSx2];
//static int64_t testInt64s[RUNSx2];
//static struct byte_8* testByte8[RUNS];
//static struct byte_128* testByte128[RUNS];
//static struct byte_1024* testByte1024[RUNS];

int main(void) {
	enum Commands inCommand;
//    getRandomInt32s((int32_t*)&testInt32s, RUNSx2);
//    getRandomInt64s((int64_t*)&testInt64s, RUNSx2);
//    getRandomByte8s((struct byte_8**)&testByte8, RUNS);
//    getRandomByte128s((struct byte_128**)&testByte128, RUNS);
    
		// oof ran out of memory allocating this to the heap
		//getRandomByte1024s((struct byte_1024**)&testByte1024, RUNS);

    timer_init();
		initCLI();
		initLED();
		clearScrean();
	
    //while(1) {
			//testWithTimer();
    //}
	
		while(1) {
		printScreenOnLine((const uint8_t*)USER_PROMPT);
		inCommand = readCommand(); 
		processCommand(inCommand);
	}
}

void testWithTimer() {
		unsigned int i;
		uint16_t volatile time = 0;
		uint16_t volatile startTime = 0;
		uint16_t volatile totalTimes[RUNS]; 
		double volatile averageTime = 0;
	
	
		static int32_t testInt32s[2];
		static int64_t testInt64s[2];
		static struct byte_8 testByte8;
		static struct byte_128 testByte128;
		static struct byte_1024 testByte1024;
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt32s(testInt32s, 2);
			
			startTime = timer_start();
			add32(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 50

		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt64s(testInt64s, 2);
			
			startTime = timer_start();
			add64(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 60
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt32s(testInt32s, 2);
			
			startTime = timer_start();
			mult32(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 48
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt64s(testInt64s, 2);
			
			startTime = timer_start();
			mult64(testInt64s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 74
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt32s(testInt32s, 2);
			
			startTime = timer_start();
			div32(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 58

		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt64s(testInt64s, 2);
			
			startTime = timer_start();
			div64(testInt64s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 75
	
		struct byte_8 testByte8Copy;
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomByte8(&testByte8);
			
			startTime = timer_start();
			copyByte8(&testByte8);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 48
		
		struct byte_128 testByte128Copy;		
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomByte128s(&testByte128);
			
			startTime = timer_start();
			testByte128Copy = copyByte128(&testByte128);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 1004
		
		struct byte_1024 testByte1024Copy;		
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomByte1024s(&testByte1024);
			
			startTime = timer_start();
			testByte1024Copy = copyByte1024(&testByte1024);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // Fails after 7 runs. Mysterious bug
}

void testAndPrintWithTimer() {
		unsigned int i;
		uint16_t volatile time = 0;
		uint16_t volatile startTime = 0;
		uint16_t volatile totalTimes[RUNS]; 
		double volatile averageTime = 0;
	
		static int32_t testInt32s[2];
		static int64_t testInt64s[2];
		static struct byte_8 testByte8;
		static struct byte_128 testByte128;
		static struct byte_1024 testByte1024;
	
		char outputStringBuffer[100];
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt32s(testInt32s, 2);
			
			startTime = timer_start();
			add32(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 50
		sprintf(&outputStringBuffer, "ADD 32 AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt64s(testInt64s, 2);
			
			startTime = timer_start();
			add64(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 60
		sprintf(&outputStringBuffer, "ADD 64 AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt32s(testInt32s, 2);
			
			startTime = timer_start();
			mult32(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 48
		sprintf(&outputStringBuffer, "MULT 32 AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt64s(testInt64s, 2);
			
			startTime = timer_start();
			mult64(testInt64s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 74
		sprintf(&outputStringBuffer, "MULT 64 AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt32s(testInt32s, 2);
			
			startTime = timer_start();
			div32(testInt32s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 58
		sprintf(&outputStringBuffer, "DIV 32 AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomInt64s(testInt64s, 2);
			
			startTime = timer_start();
			div64(testInt64s[i], testInt32s[i+1]);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 75
		sprintf(&outputStringBuffer, "DIV 64 AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		struct byte_8 testByte8Copy;
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomByte8(&testByte8);
			
			startTime = timer_start();
			copyByte8(&testByte8);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 48
		sprintf(&outputStringBuffer, "8 BYTE COPY AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		struct byte_128 testByte128Copy;		
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomByte128s(&testByte128);
			
			startTime = timer_start();
			testByte128Copy = copyByte128(&testByte128);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // 1004
		sprintf(&outputStringBuffer, "128 BYTE COPY AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
		
		struct byte_1024 testByte1024Copy;		
		
		for (i = 0; i < RUNS; i++) {
			srand(i);
			assignRandomByte1024s(&testByte1024);
			
			startTime = timer_start();
			testByte1024Copy = copyByte1024(&testByte1024);
			time = timer_stop(startTime);
			
			totalTimes[i] = time;
		}
		
		averageTime = getAverageTime(&totalTimes, RUNS); // Fails after 7 runs. Mysterious bug
		sprintf(&outputStringBuffer, "1024 BYTE COPY AVERAGE TIME: %.2lf", averageTime);
		printScreen(&outputStringBuffer);
}