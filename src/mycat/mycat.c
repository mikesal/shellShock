#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFSIZE 1024
int main(int argc, char **argv) {
  //check that it takes in arguments

  //if argc==1 -- write to screen
  int s, fd;
  char buffer[BUFFSIZE];

  if(argc ==1){
    while((s = read(STDIN_FILENO, buffer, BUFFSIZE)) > 0){
      if(write(STDOUT_FILENO, buffer, s) != s)  //read character number should match write character number
        perror("WRITE ERROR");
    }
    if(s < 0)
      perror("READ ERROR");
  }
  else{
    for(int i = 1; i < argc; i++){
      if(argv[i][0] == '-'){
        if(access(argv[i], R_OK|F_OK) == -1){ //check read access to file
          perror("ACCESS ERROR");
          exit (1);
        }
        fd = open(argv[i], O_RDONLY);
      }
      else{
        fd = STDOUT_FILENO;
      }
      while((s = read(fd, buffer, BUFFSIZE)) > 0){
        if(write(STDOUT_FILENO, buffer, s) != s)
          perror("WRITE ERROR");
      }
      if(s < 0)
        perror("READ ERROR");

      if(close(fd) == -1)
        perror("CLOSING ERROR");
    }
  }

  exit(0);
}
