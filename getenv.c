#include "shell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @info: Information struct containing relevant data.
 * @name: Name of the environment variable.
 * Return: Value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *current = info->env;

	while (current != NULL)
	{
		/* Assumes that each environment variable is in the form "NAME=VALUE" */
		char *delimiter = strchr(current->str, '=');

		if (delimiter != NULL)
		{
			/* Compare the variable name */
			if (strncmp(current->str, name, delimiter - current->str) == 0)
			{
				/* Return the value of the environment variable */
				return (delimiter + 1);
			}
		}

		current = current->next;
	}

	return (NULL); /* Variable not found */
}

/**
 * _myenv - Implementation of the 'env' builtin command.
 * @info: Information struct containing relevant data.
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	list_t *current = info->env;

	while (current != NULL)
	{
		/* Print each environment variable */
		_puts(current->str);
		_putchar('\n');

		current = current->next;
	}

	return (0);
}

/**
 * _mysetenv - Implementation of the 'setenv' builtin command.
 * @info: Information struct containing relevant data.
 * @var: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * Return: Always 0.
 */
int _mysetenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * _myunsetenv - Implementation of the 'unsetenv' builtin command.
 * @info: Information struct containing relevant data.
 * @var: Name of the environment variable to unset.
 * Return: Always 0.
 */
int _myunsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t d = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), d);
			d = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		d++;
	}
	return (info->env_changed);
}
