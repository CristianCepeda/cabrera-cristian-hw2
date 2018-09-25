#include "multiHeader.h"

int SharedVariable = 0;

int main (int argc, char* argv[]) {
  if (validateCmdLine(argc,argv) == FAIL){
    return FAIL;
  }
  printf("%s\n", "We Passed");
  return 0;
}

int validateCmdLine(int argc, char* argv[]) {
  if (numberOfArguments(argc) == FAIL) {
    return FAIL;
  }
  return PASS;
}

int numberOfArguments(argc) {
  if (argc != TOTAL_NUMBER_OF_ARGS) {
    printf("\n%s\n%s\n\n",
    "Number of arguments inputed are incorrect.",
    "Example input: ./multiThreaded 5");
    return FAIL;
  }
  return PASS;
}

// void SimpleThread(int which){
//   int num, val;
//   for(num = 0; num < 20; num++){
//     if(random() > RAND_MAX/2){
//       usleep(500);
//     }
//     val = SharedVariable;
//     printf("*** thread %d sees value %d\n", which, val);
//     SharedVariable = val + 1;
//   }
//   val = SharedVariable;
//   printf("Thread %d sees final value %d\n", which, val);
// }
