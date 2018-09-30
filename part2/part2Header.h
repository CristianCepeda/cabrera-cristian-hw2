#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//                                                          [ GLOBAL VARIABLES ]
//----------------------------------------------------------------------------->
int SharedVariable; // Used in SimpleThread()

//                                                                 [ CONSTANTS ]
//----------------------------------------------------------------------------->
enum CONSTANTS { FAIL = 0, PASS = 1, TOTAL_NUMBER_OF_ARGS = 2 };
enum ASCII { ZERO_ASCII = 48, NINE_ASCII = 57 };

//                                                     PROTOTYPES [pthreads-1.c]
//----------------------------------------------------------------------------->
int validateCmdLine(int argc, char* argv[]);
int numberOfArguments(int argc);
int checkForOnlyNumbers(int argc, char * argv[]);
void* functionCall(void* thread);
void SimpleThread(int which);

struct threadStruct {
  pthread_t id;
  int threadIndex;
};
