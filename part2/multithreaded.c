#include "multiHeader.h"

int SharedVariable = 0;

int main (int argc, char* argv[]) {
  if (validateCmdLine(argc,argv) == FAIL){
    return FAIL;
  }

  printf("argument 0 %s\n\n", argv[0]);
  printf("argument 1 %s\n\n", argv[1]);
  printf("argument 2 %s\n\n", argv[2]);
  printf("%s\n", "We Passed");
  return 0;
}

int validateCmdLine(int argc, char* argv[]) {
  if (numberOfArguments(argc) == FAIL) { return FAIL; }
  else if (checkForOnlyNumbers(argc, argv) == FAIL){ return FAIL;}
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
int checkForOnlyNumbers(int argc, char * argv[]) {
  // ********* CHECK IF THERE IS ANYTHING INPUTED BESIDES NUMBERS *************
  size_t row, column;
  for(row = 1; row < argc; row++) {
    for(column = 0; argv[row][column] != '\0'; column++) {
      int valueOfArgv = argv[row][column];
      if (valueOfArgv < ZERO_ASCII || valueOfArgv > NINE_ASCII ) { //57 is 9 and 48 is 0 in ascii
        printf("\n%s\n", "***************************************************");
        printf("%s\n%s\n",
        "There was an incorrect input value. Only positive",
        "whole values are accepted.");
        printf("\n");
        printf("%s\n\n", "***************************************************");
        return FAIL; // didn't work is the number 0
      }
    }
  }
  return PASS; // if it worked then return 1
}

// You need to create a global Variable named
// SharedVariable
// and pass in the thread ID number.
void SimpleThread(int which){
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
