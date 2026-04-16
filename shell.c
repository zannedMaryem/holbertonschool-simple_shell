#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - main entry file for simple shell.
 * @argc: number of arguments.
 * @argv : array of arguments.
 * Return: return Success.
 */
int main()
{
	int status;
	char *lineptr = NULL, *trim, *token;
	size_t line_len;
	ssize_t read_in;
	char *argv[2];
	pid_t pid;

	while (1)
	{
		/* Display prompt only if interactive */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		}
		/* read input*/
		read_in = getline(&lineptr, &line_len, stdin);
		if (read_in == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				write(STDOUT_FILENO, "\n", 1); /*-1 on failure or handle the "end of file" condition (Ctrl+D)*/
			}
			free(lineptr);
			lineptr = NULL;
			break;
		}
		/*Replace the newline character with a null terminator*/
		lineptr[strcspn(lineptr, "\n")] = '\0';
		trim = trim_spaces(lineptr);
		if (strlen(trim) == 0)
		{
			continue;
		}
		token = strtok(trim, " \t");
		if (token == NULL)
		{
			continue;
		}
		argv[0] = token;
		argv[1] = NULL;
		/*Create child process and use it to excute the command*/
		pid = fork();
		if (pid == -1) /* If fork failed*/
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) /* child process*/
		{
			if (execve(argv[0], argv, __environ) == -1)
			{
				perror("./hsh");
				exit(EXIT_FAILURE);
			}
		}
		else /*Parent prcess : wait for child*/
		{
			wait(&status);
		}
	}
	free(lineptr);
	return (EXIT_SUCCESS);
}
