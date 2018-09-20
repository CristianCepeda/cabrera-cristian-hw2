/* This example is stolen from Dr. Raju Rangaswami's original 4338
   demo and modified to fit into our lecture. */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 20
#define BUFSIZ 1024

int get_number_of_processes(char* cmdline, char* args[]) {
	int i = 0;

	/* if no args */
	if ((args[0] = strtok(cmdline, ";")) == NULL)
		return 0;

	while ((args[++i] = strtok(NULL, ";")) != NULL) {
		if (i >= MAX_ARGS) {
			printf("Too many arguments!\n");
			exit(1);
		}
	}
	/* the last one is always NULL */
	return i;
}


int* get_args(char* cmdline, char* args[][], int num_of_procs, char* procs[])
{
  int nargs[num_of_procs];
  for (int j = 0; j < num_of_procs; j++) {
	  int i = 0;
	  /* if no args */
	  if ((args[0][0] = strtok(procs[j], "\n\t ")) == NULL)
		  return 0;

	  while ((args[j][++i] = strtok(NULL, "\n\t ")) != NULL) {
		  if (i >= MAX_ARGS) {
			  printf("Too many arguments!\n");
			  exit(1);
		  }
	  }

	  nargs[j] = i;
  }
  /* the last one is always NULL */

  return nargs;
}

void execute(char* cmdline)
{
  int pid, async;
  char* procs[MAX_ARGS];
  int num_of_procs = get_number_of_processes(cmdline, procs);
  // Multi Dimensional Array of Proccesses
  char* args[num_of_procs][MAX_ARGS];

  if (num_of_procs <= 0) return;

  int* nargs = get_args(cmdline, args, num_of_procs, args_procs);



  if(!strcmp(args[0][0], "quit") || !strcmp(args[0][0], "exit")) {
    exit(0);
  }


  for (int i = 0; i < num_of_procs; i++) {

	  /* check if async call */
	  if (!strcmp(args[nargs[i]- 1], "&")) { async = 1; args[--nargs] = 0; }
	  else async = 0;

	  pid = fork();
	  if (pid == 0) { /* child process */
		  execvp(args[0], args);
		  /* return only when exec fails */
		  perror("exec failed");
		  exit(-1);
	  }
	  else if (pid > 0) { /* parent process */
		  if (!async) waitpid(pid, NULL, 0);
		  else printf("this is an async call\n");
	  }
	  else { /* error occurred */
		  perror("fork failed");
		  exit(1);
	  }

  }


}

int main (int argc, char* argv [])
{
  char cmdline[BUFSIZ];

  for(;;) {
    printf("JohnSmith> ");
    if(fgets(cmdline, BUFSIZ, stdin) == NULL) {
      perror("fgets failed");
      exit(1);
    }
    execute(cmdline) ;
  }
  return 0;
}
