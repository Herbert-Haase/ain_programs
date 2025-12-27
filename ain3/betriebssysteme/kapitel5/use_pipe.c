#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 100
int fildes[2];
char buf[BUFSIZE];


int main(void){
  if(pipe(fildes) == -1) {
    perror("pipe failed");
    exit(1);
  }
  int rc = fork();
  if (rc < 0){
    perror("fork failed");
    exit(1);
  } else if(rc == 0){
    strcpy(buf,"child");
    close(fildes[0]);
    write(fildes[1],buf,BUFSIZE);
    close(fildes[1]);
  } else{
    int status;
    int wc = waitpid(rc,&status,0);

    close(fildes[1]);
    read(fildes[0],buf,BUFSIZE);
    close(fildes[0]);

    printf("my child told me: %s\n",buf);
  }
  return 0;
}
