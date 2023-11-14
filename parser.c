#include "shell.h"

/**
 * is_cmd - Check if a command is built-in or in the PATH.
 * @info: Structure containing arguments and information.
 * @cmd: Command to check.
 * Return: 1 if built-in, 0 if not.
 */
int is_cmd(info_t *info, char *cmd)
{
	for (int i = 0; info->builtin[i].type != NULL; i++)
	{
		if (_strcmp(info->builtin[i].type, cmd) == 0)
			return (1); /* Found as a built-in command */
	}
	return (0); /* Not a built-in command */
}

/**
 * dup_chars - Duplicate a range of characters from a string.
 * @str: Source string.
 * @start: Starting index.
 * @end: Ending index.
 * Return: Duplicated substring.
 */
char *dup_chars(char *str, int start, int end)
{
	char *result;
	int len = end - start + 1;

	if (len <= 0)
		return (NULL);

	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);

	for (int i = 0; i < len; i++)
	{
		result[i] = str[start + i];
	}
	result[len] = '\0'; /* Null-terminate the string */
	return (result);
}

/**
 * find_path - Find the full path of a command in the PATH variable.
 * @info: Structure containing arguments and information.
 * @cmd: Command to find.
 * @separator: Path separator character.
 * Return: Full path if found, otherwise cmd.
 */
char *find_path(info_t *info, char *cmd, char *separator)
{
	char *path_var = _getenv(info, "PATH");
	char *token, *path;
	struct stat st;

	if (path_var == NULL)
		return (cmd); /* PATH not set, return the command as is */

	token = strtok(path_var, separator);
	while (token != NULL)
	{
		path = _strcat(token, "/");
		path = _strcat(path, cmd);
		if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
		{
			free(path_var);
			return (path); /* Command found in this path */
		}
		free(path);
		token = strtok(NULL, separator);
	}

	free(path_var);
	return (cmd); /* Command not found in PATH, return as is */
}
