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
	char *prompt = "& ";

	if (argc < 2)
	{
		write(STDOUT_FILENO, "Usage: ./hsh command [args...]\n", 32);
		return (EXIT_FAILURE);
	}

	write(STDOUT_FILENO, prompt, 2);
	if (fork() == 0)
	{
		execvp(argv[1], argv + 1);
		perror(argv[1]);
		_exit(EXIT_FAILURE);
	}
	wait(&status);
	return (EXIT_SUCCESS);
}
