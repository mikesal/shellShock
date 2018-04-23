#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "pwd.h"

int mycd(char** args)
{
	if (args[1] == NULL) 
    	fprintf(stderr, "mysh: expected argument to \"cd\"\n");
  	else if (chdir(args[1]) != 0)
    	perror("mysh");
 
  	return 1;
}
