#include "shell.h"

/**
 * interactive - Checks if the shell is in interactive mode
 * @info: Pointer to the info_t struct
 *
 * Return: 1 if interactive, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if the character is a delimiter
 * @c: Character to check
 * @delim: Delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks if the character is alphabetic
 * @c: Character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - Converts a string into an integer
 * @s: String to convert
 * Return: If no numbers in the string, 0; otherwise, the converted number
 */
int _atoi(char *s)
{
	int d, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (d = 0; s[d] != '\0' && flag != 2; d++)
	{
		if (s[d] == '-')
			sign *= -1;

		if (s[d] >= '0' && s[d] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[d] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	output = (sign == -1) ? -result : result;

	return (output);
}
