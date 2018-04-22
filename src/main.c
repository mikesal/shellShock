#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "prompt.h"
#include "pwd.h"
#include "cd.h"

char cwd[1024];
char commandPrompt[2048];

int main(int argc, char* argv[])
{
	char usrInpt[1024];
	getPrompt();
	
	while (usrInpt[0] != 'q')
	{
		cwd[0] = '\0';
		getCWD();
		commandPrompt[0] = '\0';
		getPrompt();
		
		printf("%s", commandPrompt);
		fgets(usrInpt, sizeof(usrInpt), stdin);
		
		if(strstr(usrInpt, "mypwd") == usrInpt)
			printf("%s\n", cwd);
		if(strstr(usrInpt, "mycd") == usrInpt)
			changeDir(usrInpt);
	}
	
	return 0;
}
