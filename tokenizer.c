#include "shell.h"

/**
 * **strtow - splits a string into words and ignores repeat delimiters
 * @str: This is the input string
 * @d: This is the delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, a, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, a = 0; a < numwords; a++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
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
			s[a][m] = str[i++];
		s[a][m] = 0;
	}
	s[a] = NULL;
	return (s);
}

/**
 * **strtow2 - This splits a string into words
 * @str: This is the input string
 * @d: This is the delimiter
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, a, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, a = 0; a < numwords; a++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
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
			s[a][m] = str[i++];
		s[a][m] = 0;
	}
	s[a] = NULL;
	return (s);
}
