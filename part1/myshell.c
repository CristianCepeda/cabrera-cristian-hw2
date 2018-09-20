/* This example is stolen from Dr. Raju Rangaswami's original 4338
   demo and modified to fit into our lecture. */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 20
#define BUFSIZ 1024

//To separete process by semicolons :)
int get_process(char* cmdline, char* process[])
{
  int i = 0;

  /* if no process */
  if((process[0] = strtok(cmdline, ";")) == NULL)
    return 0;

  while((process[++i] = strtok(NULL, ";")) != NULL) {
    if(i >= MAX_ARGS) {
      printf("Too many arguments!\n");
      exit(1);
    }
  }
  /* the last one is always NULL */
  return i;
}

int get_args(char* cmdline, char* args[][MAX_ARGS], char* process[], int num_processes)
{
  int j;

  for (int x = 0; x < num_processes; x++){
  int i = 0;
  /* if no args */
  if((args[0][0] = strtok(process[x], "\n\t ")) == NULL)
    return 0;

  while((args[x][++i] = strtok(NULL, "\n\t ")) != NULL) {
    if(i >= MAX_ARGS) {
      printf("Too many arguments!\n");
      exit(1);
    }
  }
  j = i;
}
  /* the last one is always NULL */
  return j;
}


void execute(char* cmdline)
{
  int pid, async;
  char* process[MAX_ARGS];

  int num_processes = get_process(cmdline, process);

  char* args[num_processes][MAX_ARGS];



  int nargs = get_args(cmdline, args,process, num_processes);
  if(nargs <= 0) return;

/*
strcmp() compares two strings
Returns 0 if they are equal which will make the if statement true
and thus
*/

for(int i; i < num_processes; i++){

  int j = 0;
  char* check_args[MAX_ARGS];

  while(args[i][++j] != NULL){

  check_args[0] = args[i][++j];

  if(!strcmp(check_args[0], "quit") || !strcmp(check_args[0], "exit")) {
    exit(0);
  }

  /* check if async call */
  if(!strcmp(check_args[nargs-1], "&")) { async = 1; check_args[--nargs] = 0; }
  else async = 0;

  pid = fork();
  if(pid == 0) { /* child process */
    execvp(check_args[0], check_args);
    /* return only when exec fails */
    perror("exec failed");
    exit(-1);
  } else if(pid > 0) { /* parent process */
    if(!async) waitpid(pid, NULL, 0);
    else printf("PID %d\n", getpid());
  } else { /* error occurred */
    perror("fork failed");
    exit(1);
  }
}
}

}

int main (int argc, char* argv [])
{
  char cmdline[BUFSIZ];

  for(;;) {
    printf("Cabrera-Cristian> ");
    if(fgets(cmdline, BUFSIZ, stdin) == NULL) {
      perror("fgets failed");
      exit(1);
    }
    /*Reads the buffer or the input that was placed by the user*/
    execute(cmdline) ;
  }
  return 0;
}
