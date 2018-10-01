#include "part2Header.h"

/*                                                                     [ STEPS ]
------------------------------------------------------------------------------->
1 - Validate Users input
2 - Initialize global shared variable.
3 - Create array with the number of threads desired. And have them call
    functionCall()
4 - Join the threads and suspend the execution of the calling thread.
*/

int main (int argc, char* argv[]) {
  //                                                                  [ STEP 1 ]
  //--------------------------------------------------------------------------->
  if (validateCmdLine(argc,argv) == FAIL){
    return FAIL;
  }

  //                                                                  [ STEP 2 ]
  //--------------------------------------------------------------------------->
  SharedVariable = 0;
  int NUMBER_OF_THREADS = atoi(argv[1]);
  pthread_barrier_init(&mybarrier, NULL, THREAD_COUNT + 1);


  //                                                                  [ STEP 3 ]
  //--------------------------------------------------------------------------->
  struct threadStruct* threadPTR = (struct threadStruct*)malloc(NUMBER_OF_THREADS*sizeof(struct threadStruct));

  for (size_t i = 0; i < NUMBER_OF_THREADS; i++) {
    threadPTR[i].threadIndex = i;
    pthread_create(&threadPTR[i].id, NULL, functionCall, &threadPTR[i]);
  }

  //                                                                  [ STEP 4 ]
  //--------------------------------------------------------------------------->
  for (size_t i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(threadPTR[i].id, NULL);
  }

  return 0;
}

int validateCmdLine(int argc, char* argv[]) {
  if (numberOfArguments(argc) == FAIL) { return FAIL; }
  else if (checkForOnlyNumbers(argc, argv) == FAIL){ return FAIL;}
  return PASS;
}
int numberOfArguments(argc) {
  if (argc != TOTAL_NUMBER_OF_ARGS) {
    printf("\n%s\n", "***************************************************");
    printf("\n%s\n%s\n",
    "Number of arguments inputed are incorrect.",
    "Example input: ./multiThreaded 5");
    printf("\n%s\n\n", "***************************************************");
    return FAIL;
  }
  return PASS;
}
int checkForOnlyNumbers(int argc, char * argv[]) {
  // ********* CHECK IF THERE IS ANYTHING INPUTED BESIDES NUMBERS *************
  size_t row, column;
  for(row = 1; row < argc; row++) {
    for(column = 0; argv[row][column] != '\0'; column++) {
      int valueOfArgv = argv[row][column];
      if (valueOfArgv < ZERO_ASCII || valueOfArgv > NINE_ASCII ) { //57 is 9 and 48 is 0 in ascii
        printf("\n%s\n", "***************************************************");
        printf("\n%s\n%s\n",
        "There was an incorrect input value. Only positive",
        "whole values are accepted.");
        printf("\n%s\n\n", "***************************************************");
        return FAIL; // didn't work is the number 0
      }
    }
  }
  return PASS; // if it worked then return 1
}
void* functionCall(void* thread){
  struct threadStruct* individualThread = (struct threadStruct*)thread;
  int ID = individualThread->threadIndex;
  SimpleThread(ID);
  return NULL;
}

// You need to create a global Variable named
// SharedVariable
// and pass in the thread ID number.
void SimpleThread(int which) {
  int num, val;
  for(num = 0; num < 20; num++){
    if(random() > RAND_MAX/2){
      usleep(500);
    }
    val = SharedVariable;
    printf("*** thread %d sees value %d\n", which, val);
    SharedVariable = val + 1;
  }
  val = SharedVariable;
  printf("Thread %d sees final value %d\n", which, val);
}
