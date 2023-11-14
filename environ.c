#include "shell.h"

/**
 * _myenv - Display the environment.
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	char **env = get_environ(info);
	int i = 0;

	while (env && env[i])
	{
		_puts(env[i]);
		_putchar('\n');
		i++;
	}

	return (0);
}

/**
 * _mysetenv - Set an environment variable.
 * @info: Parameter struct.
 *
 * Return: Always 0 on success, 1 on error.
 */
int _mysetenv(info_t *info)
{
	char *key, *value;

	if (info->argc != 3)
	{
		print_error(info, "Usage: setenv VARIABLE VALUE");
		return (1);
	}

	key = info->argv[1];
	value = info->argv[2];

	if (_setenv(info, key, value) == -1)
	{
		print_error(info, "Error setting environment variable");
		return (1);
	}

	return (0);
}

/**
 * _myunsetenv - Unset an environment variable.
 * @info: Parameter struct.
 *
 * Return: Always 0 on success, 1 on error.
 */
int _myunsetenv(info_t *info)
{
	char *key;

	if (info->argc != 2)
	{
		print_error(info, "Usage: unsetenv VARIABLE");
		return (1);
	}

	key = info->argv[1];

	if (_unsetenv(info, key) == -1)
	{
		print_error(info, "Error unsetting environment variable");
		return (1);
	}

	return (0);
}

/**
 * populate_env_list - Populate the environ list from the current environ
 * @info: Parameter struct.
 *
 * Return: 0 on success, -1 on failure.
 */
int populate_env_list(info_t *info)
{
	char **env = environ;
	int i = 0;

	while (env && env[i])
	{
		if (add_node_end(&(info->env), env[i], i) == NULL)
			return (-1);
		i++;
	}

	return (0);
}
