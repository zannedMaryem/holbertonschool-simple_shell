#include "shell.h"
#include <string.h>
/**
 * trim_spaces - remove leading and trailing spaces
 * @str: input string
 *
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	/* Skip leading spaces */
	while (*str == ' ')
		str++;

	if (*str == '\0')
		return str;

	/* Remove trailing spaces */
	end = str + strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;

	*(end + 1) = '\0';

	return str;
}
