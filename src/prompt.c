#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "pwd.h"

char commandPrompt[2048];

void getPrompt()
{
	char hostname[1024];
	hostname[1023] = '\0';
	char user[1024];
	user[1023] = '\0';
	commandPrompt[0] = '\0';
	char cwd[1024];
	cwd[0] = '\0';
	getcwd(cwd, sizeof(cwd));
	char homeDir[1024];
	homeDir[0] = '\0';
	strcat(homeDir, "/home/");
	strcat(homeDir, user);
		
	if (strcmp(cwd, homeDir)==0)
	{
		cwd[0] = '~';
		cwd[1] = '\0';
	}
	else if (strcmp(cwd, "/home") <= 0)
		cwd[0] = '~';
	else if (strstr(cwd, "home") != NULL)
	{
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
	}
	
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
	
	printf("%s", commandPrompt);
	
	return;
}