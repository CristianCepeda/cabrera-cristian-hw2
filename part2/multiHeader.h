#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// ENUM CONSTANTS
enum CONSTANTS {FAIL = 0, PASS = 1, TOTAL_NUMBER_OF_ARGS = 2};
enum ASCII{ZERO_ASCII = 48, NINE_ASCII = 57};

int validateCmdLine(int argc, char* argv[]);
int numberOfArguments(int argc);
int checkForOnlyNumbers(int argc, char * argv[]);
void SimpleThread(int which);

// GLOBAL VARIABLES
int SharedVariable; // Used in SimpleThread()
