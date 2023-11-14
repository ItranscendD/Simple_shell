#include "shell.h"

/**
 * _atoi - Converts a string to an integer
 * @str: The input string
 *
 * Return: The converted integer, or -1 on error
 */
int _atoi(char *str)
{
	int result = 0;
	int sign = 1;

	if (str == NULL)
		return (-1);

	while (*str)
	{
		if (*str == '-')
			sign *= -1;
		else if (*str >= '0' && *str <= '9')
			result = result * 10 + (*str - '0');
		else
			return (-1);

		str++;
	}

	return (result * sign);
}
