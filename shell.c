#include "shell.h"
#include <stdlib.h>
#include <stdarg.h>
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
	(void)argc;

	if (fork == 0)
	{
		execvp(argv[1], argv + 1);
	}
	wait(&status);
	return (EXIT_SUCCESS);
}
