#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "mypwd.h"

void changeDir(char* path)
{
	int pathStart = 0;
	
	for (int i = 0; i <= strlen(path); i++)
	{
		if (pathStart > 0)
			path[i-pathStart] = path[i];
		if (path[i] == ' ')
			pathStart = i+1;
	}
	path[strlen(path)-1] = '\0';
	
	chdir(path);
}
