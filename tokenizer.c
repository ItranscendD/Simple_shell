#include "shell.h"

/**
 * **strtow - splits a str into words and ignores repeat delimiters
 * @str: This is the input string
 * @d: This is the delimiter string
 * Return: As a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int a, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (d = 0; str[d] != '\0'; d++)
		if (!is_delim(str[d], d) && (is_delim(str[d + 1], d) || !str[d + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (d = 0, a = 0; a < numwords; a++)
	{
		while (is_delim(str[d], d))
			d++;
		k = 0;
		while (!is_delim(str[d + k], d) && str[d + k])
			k++;
		s[a] = malloc((k + 1) * sizeof(char));
		if (!s[a])
		{
			for (k = 0; k < a; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[a][m] = str[d++];
		s[a][m] = 0;
	}
	s[a] = NULL;
	return (s);
}

/**
 * **strtow2 - This splits a string into words
 * @str: This is the input string
 * @d: This is the delimiter
 * Return: As a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (d = 0; str[d] != '\0'; d++)
		if ((str[d] != d && str[d + 1] == d) ||
		    (str[d] != d && !str[d + 1]) || str[d + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (d = 0, a = 0; a < numwords; a++)
	{
		while (str[d] == d && str[d] != d)
			d++;
		k = 0;
		while (str[d + k] != d && str[d + k] && str[d + k] != d)
			k++;
		s[a] = malloc((k + 1) * sizeof(char));
		if (!s[a])
		{
			for (k = 0; k < a; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[a][m] = str[d++];
		s[a][m] = 0;
	}
	s[a] = NULL;
	return (s);
}
