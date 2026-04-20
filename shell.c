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
extern char **environ;

int main()
{
	int status, i;
	char *lineptr = NULL, *trim, *token;
	size_t line_len;
	ssize_t read_in;
	char *argv[64];

	while (1)
	{
		/* Display prompt only if interactive */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		}
		/* read input*/
		read_in = getline(&lineptr, &line_len, stdin); /*returns -1 on failure or the "end of file" condition (Ctrl+D)*/
		if (read_in == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				write(STDOUT_FILENO, "\n", 1); /*Exit with new line in interactive mode*/
			}
			free(lineptr);
			lineptr = NULL;
			break;
		}
		/*Evaluate input*/
		/*Replace the newline character with a null terminator*/
		lineptr[strcspn(lineptr, "\n")] = '\0';
		/*removes spaces before and after command line*/
		trim = trim_spaces(lineptr);
		if (strlen(trim) == 0)
		{
			/* Free the trimmed string (same as lineptr since trim_spaces modifies in-place) */
			free(trim);
			/* Reset lineptr to NULL for safe reuse by getline in next iteration */
			lineptr = NULL;
			continue;
		}
		/*Handle multi-word commands*/
		i = 0;
		token = strtok(trim, " \t");
		while (token != NULL && i < 63)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
		{
			/* Free the trimmed string to prevent memory leak */
			free(trim);
			/* Reset lineptr to NULL for safe reuse by getline */
			lineptr = NULL;
			continue;
		}
		/*Handle PATH and do not fork if command does not exist*/
		/*??????????*/

		/*Create child process and use it to excute the command*/
		if (fork() == -1) /* If fork failed*/
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		if (fork() == 0) /* child process*/
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else /*Parent prcess : wait for child*/
		{
			wait(&status);
			/* Free the trimmed string to prevent memory leak */
			free(trim);
			/* Reset lineptr to NULL for safe reuse by getline in next iteration */
			lineptr = NULL;
		}
	}
	free(lineptr);
	return (EXIT_SUCCESS);
}
