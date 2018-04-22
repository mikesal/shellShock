#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "pwd.h"

char commandPrompt[2048];

char* getPrompt()
{
	char hostname[1024];
	hostname[1023] = '\0';
	char user[1024];
	user[1023] = '\0';
	*commandPrompt = '\0';
	char cwd[1024];
	strcat(cwd, getCWD());
	
	cwd[0] = '~';
	cwd[1] = '/';
	int index = 0;
	int slash = -1;
	int i;
		
	for (i = 2; i < strlen(cwd); i++)
	{
		if (index > 0)
			cwd[i-index+1] = cwd[i];
		if (slash == 0 && cwd[i] == '/' && index == 0)
			index = i;
		if (cwd[i] == '/')
			slash = 0;
	}
	cwd[i-index+1] = '\0';

	
	gethostname(hostname, 1023);
	getlogin_r(user, 1023);
	
	strcat(commandPrompt, user);
	strcat(commandPrompt, "@");
	strcat(commandPrompt, hostname);
	strcat(commandPrompt, ":");
	strcat(commandPrompt, cwd);
	strcat(commandPrompt, "$ ");
	
	size_t len = strlen(commandPrompt);
	commandPrompt[len] = '\0';
	
	return commandPrompt;
}