#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MYSH_RL_BUFSIZE 1024
char *read_line(void)
{
  int bufsize = MYSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;
  if (!buffer) 
  {
    fprintf(stderr, "mysh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while (1) 
  {
    c = getchar();
    if (c == EOF || c == '\n') 
    {
      buffer[position] = '\0';
      return buffer;
    } 
    else 
    {
      buffer[position] = c;
    }
    position++;
    if (position >= bufsize) 
    {
      bufsize += MYSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) 
      {
        fprintf(stderr, "mysh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
char **split_line(char *line)
{
  int bufsize = TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) 
  {
    fprintf(stderr, "mysh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strtok(line, TOK_DELIM);
  while (token != NULL) 
  {
    tokens[position] = token;
    position++;
    if (position >= bufsize) 
    {
      bufsize += TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) 
      {
        free(tokens_backup);
        fprintf(stderr, "mysh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}