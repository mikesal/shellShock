#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char cwd[1024];

int mypwd(char** args)
{
	cwd[1023] = '\0';
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);

	return 1;	
}