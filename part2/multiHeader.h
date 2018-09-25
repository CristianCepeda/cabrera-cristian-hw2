#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

// ENUM CONSTANTS
enum CONSTANTS {FAIL = 0, PASS = 1, TOTAL_NUMBER_OF_ARGS = 2};

int validateCmdLine(int argc, char* argv[]);
int numberOfArguments(int argc);
// void SimpleThread(int which);
