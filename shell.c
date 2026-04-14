#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * main - main entry file for simple shell.
 * @argc: number of arguments.
 * @argv : array of arguments.
 * Return: return Success.
 */
int main(int argc, char *argv[])
{
	int status;
	char *lineptr = NULL;
	size_t line_len;
	ssize_t read_in;
	(void)argc;

/* if (argc < 2)
	{
		write(STDOUT_FILENO, "Usage: ./hsh command [args...]\n", 32);
		return (EXIT_FAILURE);
	}*/
	while(1)
	{
		/* display prompt*/
		write(STDOUT_FILENO, "$ ", 2);
		/* read input*/
		read_in = getline(&lineptr, &line_len, stdin);
		if (read_in == -1)
		{
			write(STDOUT_FILENO,"\n", 2); /*-1 on failure or handle the "end of file" condition (Ctrl+D)*/
			free(lineptr);
			break;
		}
		if (fork() == 0)
		{
			execv(argv[1], argv + 1);
			perror("No such file or directory");
		}
		wait(&status);
		
	}
	free(lineptr);
	return (EXIT_SUCCESS);
}
