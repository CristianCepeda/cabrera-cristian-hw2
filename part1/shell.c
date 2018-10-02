#include "shell.h"

int get_args(char* cmdline, char* args[])
{
  int i = 0;

  /* if no args */
  if((args[0] = strtok(cmdline, "\n\t ")) == NULL)
    return 0;

  while((args[++i] = strtok(NULL, "\n\t ")) != NULL) {
    if(i >= MAX_ARGS) {
      printf("Too many arguments!\n");
      exit(1);
    }
  }
  /* the last one is always NULL */
  return i;
}

void execute(char* cmdline)
{
  int pid, async;
  char* args[MAX_ARGS];

  int nargs = get_args(cmdline, args);
  if(nargs <= 0) return;


  if(!strcmp(args[0], "exit")) {
    exit(0);
  }

  if(!strcmp(args[0], "quit")){
    while(waitpid(-1, NULL, 0) > 0) {};
    exit(0);
  }

  if(!strcmp(args[0], "ps") || !strcmp(args[0], "/bin/ps")) {
    zombies();
  }

  /* check if async call */
  if(!strcmp(args[nargs-1], "&")) { async = 1; args[--nargs] = 0; }
  else async = 0;

  pid = fork();
  if(pid == 0) { /* child process */
    execvp(args[0], args);
    /* return only when exec fails */
    perror("exec failed");
    exit(-1);
  } else if(pid > 0) { /* parent process */
    if(!async) waitpid(pid, NULL, 0);
    else printf("PID: %d\n", pid);
  } else { /* error occurred */
    perror("fork failed");
    exit(1);
  }
}



int main (int argc, char* argv [])
{
  char cmdline[BUFSIZ];

  for(;;) {
    printf("Cabrera, Cepeda > ");
    if(fgets(cmdline, BUFSIZ, stdin) == NULL) {
      while(waitpid(-1, NULL, 0) > 0) {};
      printf("\n");
      exit(0);
    }
      processes(cmdline);
  }
  return 0;
}

/* Deletes all zombie child processes */
void zombies(){
    int saved_errno = errno;
    while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
    errno = saved_errno;
}

/* Separetes the input but semicolen */
void processes(char* cmdline){

  char* procs[MAX_ARGS];
  int i = 0;

  if((procs[0] = strtok(cmdline, ";")) == NULL)
    return;

  while((procs[++i] = strtok(NULL, ";")) != NULL) {
    if(i >= MAX_ARGS) {
      printf("Too many arguments!\n");
      exit(1);
    }
  }
  /* Call execute each proccesses */
  for(int j = 0; j < i; j++){
  execute(procs[j]);
  }
}
