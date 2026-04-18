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
	char *lineptr = NULL, *trim, *token, *command_path;
	size_t line_len;
	ssize_t read_in;
	char *argv[64];
	pid_t pid;

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
			continue;
		}
		/*Handle PATH and do not fork if command does not exist*/
		/* Initialize command_path to NULL */
		command_path = NULL;
		/* Check if the command contains a '/', indicating a full path */
		if (strchr(argv[0], '/') != NULL)
		{
			/* If it's a full path, check if it's executable */
			if (access(argv[0], X_OK) == 0)
			{
				command_path = argv[0];
			}
		}
		else
		{
			/* If not a full path, search in PATH */
			char *path_str = get_path();
			if (path_str)
			{
				/* Duplicate the PATH string for tokenization */
				char *path_copy = strdup(path_str);
				/* Get the first directory from PATH */
				char *dir = strtok(path_copy, ":");
				/* Loop through each directory in PATH */
				while (dir)
				{
					/* Buffer to hold the candidate full path */
					char candidate[1024];
					int len;
					/* Build the candidate path: dir/command */
					len = snprintf(candidate, sizeof(candidate), "%s/%s", dir, argv[0]);
					/* Check if the path was built successfully and is executable */
					if (len >= 0 && (size_t)len < sizeof(candidate) && access(candidate, X_OK) == 0)
					{
						/* Found executable command, duplicate the path */
						command_path = strdup(candidate);
						break;
					}
					/* Move to the next directory in PATH */
					dir = strtok(NULL, ":");
				}
				/* Free the duplicated PATH string */
				free(path_copy);
			}
		}
		/* If command was not found, print error and skip execution */
		if (command_path == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			continue;
		}
		/* Set argv[0] to the full path of the command */
		argv[0] = command_path;
		/*Create child process and use it to excute the command*/
		pid = fork();
		if (pid == -1) /* If fork failed*/
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) /* child process*/
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
		}
	}
	free(lineptr);
	return (EXIT_SUCCESS);
}
