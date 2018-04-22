#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char cwd[1024];

char* getCWD()
{
	cwd[1023] = '\0';
	getcwd(cwd, sizeof(cwd));

	return cwd;	
}