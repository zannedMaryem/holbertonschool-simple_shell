#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

/**
 * get_path - retrieve PATH from environ
 *
 * Return: pointer to PATH string (without "PATH="), or NULL if not found
 */
char *get_path(void)
{
    int i = 0;

    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            return (environ[i] + 5); /* skip "PATH=" */
        }
        i++;
    }
    return (NULL);
}