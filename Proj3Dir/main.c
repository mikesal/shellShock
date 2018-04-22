#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "prompt.h"
#include "pwd.h"

char cwd[1024];
char commandPrompt[2048];

int main(int argc, char* argv[])
{
	char usrInpt[1024];
	getPrompt();
	
	while (usrInpt[0] != 'q')
	{
		printf("%s", commandPrompt);
		fgets(usrInpt, sizeof(usrInpt), stdin);
		
		if(strcmp(usrInpt, "mypwd\n") == 0)
		{
			getCWD();
			printf("%s\n", cwd);
		}
	}
	
	return 0;
}
