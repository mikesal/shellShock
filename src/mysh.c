#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "parse.h"

int mycd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "mysh: expected argument to \"cd\"\n");
  }
  else {
    if (chdir(args[1]) != 0) {
      perror("mysh");
    }
  }
  return 1;
}

int mypwd(char **args) {
  char *p;
  p = getcwd(NULL, 0);
  printf("%s\n",p);
  free(p); p=NULL;
  return 1;
}

char *builtin_str[] = {
  "mypwd",
  "mycd",
};

int (*builtin_func[]) (char **) = {
  &mypwd,
  &mycd,
};

int execute(char **args) {
  pid_t pid;
  int status;
  if ((pid = fork()) < 0) {
        printf("fork() failed!\n");
        exit(1);
  }
  if (pid == 0) { //child process
    int in=0, out=0;
    char input[64], output[64];
    for(int i=0;args[i]!= NULL;i++) {
      if(strcmp(args[i],"<")==0 || strcmp(args[i], ">")==0 || strcmp(args[i], "|")==0) {
        if(strcmp(args[i],">")==0) {
          args[i]=NULL;
          strcpy(output,args[i+1]);
          out=2;
        }
        else if(strcmp(args[i], "<")==0) {
          args[i]=NULL;
          strcpy(input,args[i+1]);
          in=2;
        }
        else {
          int     fd[2];
          pid_t   childpid;
          pipe(fd);
          if ((childpid = fork()) < 0) {
            printf("fork() failed!\n");
            exit(1);
          }
          else if((childpid) == 0) {
            close(0);
            dup(fd[0]);
            execlp(".", args[0], NULL);
          }
          else {
            while (!(wait(&status) == childpid)) ;
            close(2);
            close(1);
            dup(fd[1]);
            execlp(".", args[2], NULL);
          }
          exit(1);
        }
      }
    }

    if (in) {
      if(access(input, F_OK | R_OK)) {
        perror("mysh");
        exit(1);
      }
      int fd0 = open(input, O_RDONLY);
      dup2(fd0, 0);
      close(fd0);
    }
    if (out) {
      int fd1 = creat(output , 0644) ;
      dup2(fd1, STDOUT_FILENO);
      close(fd1);
    }
    execvp(args[0], args);
    fprintf(stderr, "Failed to exec %s\n", args[0]);
    exit(1);
  }
  else {
      while (!(wait(&status) == pid)) ;
  }
  return 1;
}

int built_or_extern(char **args) {
  if (args[0] == NULL) {
    return 1;
  }
  for (int i = 0; i < (sizeof(builtin_str) / sizeof(char *)); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return execute(args);
}

int main(int argc, char **argv) {
  char *line;
  char **args = NULL;
  int flag;

  do {
    printf("mysh >> ");
    line = read_line();
    args = split_line(line);
    flag = built_or_extern(args);

    free(line);
    free(args);
  } while (flag);
  return EXIT_SUCCESS;
}
