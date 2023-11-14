#include "shell.h"

/**
 * strtow - Tokenize a string into words.
 * @str: String to be tokenized.
 * @delim: Delimiter used for tokenization.
 * Return: Array of strings containing tokens.
 */
char **strtow(char *str, char *delim)
{
	if (str == NULL || delim == NULL)
		return (NULL);

	int i, j, k, len, count = 0;
	char **tokens;

	len = _strlen(str);
	tokens = malloc((len + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		if (is_delim(str[i], delim))
			continue;

		for (j = i; str[j] && !is_delim(str[j], delim); j++)
			;

		tokens[count] = malloc((j - i + 1) * sizeof(char));
		if (tokens[count] == NULL)
		{
			for (k = 0; k < count; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}

		for (k = 0; k < j - i; k++)
			tokens[count][k] = str[i + k];
		tokens[count][k] = '\0';
		count++;
		i = j;
	}

	tokens[count] = NULL;
	return (tokens);
}

/**
 * strtow2 - Tokenize a string into words.
 * @str: String to be tokenized.
 * @delim: Delimiter used for tokenization.
 * Return: Array of strings containing tokens.
 */
char **strtow2(char *str, char delim)
{
	if (str == NULL)
		return (NULL);

	int i, j, k, len, count = 0;
	char **tokens;

	len = _strlen(str);
	tokens = malloc((len + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		if (str[i] == delim)
			continue;

		for (j = i; str[j] && str[j] != delim; j++)
			;

		tokens[count] = malloc((j - i + 1) * sizeof(char));
		if (tokens[count] == NULL)
		{
			for (k = 0; k < count; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}

		for (k = 0; k < j - i; k++)
			tokens[count][k] = str[i + k];
		tokens[count][k] = '\0';
		count++;
		i = j;
	}

	tokens[count] = NULL;
	return (tokens);
}
