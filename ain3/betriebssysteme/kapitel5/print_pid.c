#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(void){
  printf("hello from parent %d\n",(int)getpid());
  int rc = fork();
  if (rc < 0){
    perror("fork failed");
    exit(1);
  } else if(rc == 0){
    printf("hello from child %d\n",(int)getpid());
  } else{
    int status;
    // int wc = wait(&status);
    int wc = waitpid(rc,&status,0);
    printf("hello from parent, (wc:%d), (child PID from rc:%d, with status:%d), (my pid:%d)\n",(int)wc,(int)rc, (int)status, (int)getpid());
  }
  return 0;
}

