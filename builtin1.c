#include "shell.h"

/**
 * display_history - Displays the command history with line numbers,
 *                   starting at 0.
 * @info: Structure containing potential arguments, maintaining
 *        constant function prototype.
 * Return: Always returns 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias from the list.
 * @info: Parameter struct.
 * @str: The string representing the alias.
 * Return: Returns 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *str)
{
	char *equals, temp;
	int result;

	equals = _strchr(str, '=');
	if (!equals)
		return (1);
	temp = *equals;
	*equals = 0;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equals = temp;
	return (result);
}

/**
 * add_alias - Adds an alias to the list.
 * @info: Parameter struct.
 * @str: The string representing the alias.
 * Return: Returns 0 on success, 1 on error.
 */
int add_alias(info_t *info, char *str)
{
	char *equals;

	equals = _strchr(str, '=');
	if (!equals)
		return (1);
	if (!*++equals)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_single_alias - Prints a single alias string.
 * @node: The alias node.
 * Return: Returns 0 on success, 1 on error.
 */
int print_single_alias(list_t *node)
{
	char *equals, *alias;

	if (node)
	{
		equals = _strchr(node->str, '=');
		for (alias = node->str; alias <= equals; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(equals + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Manages the alias command.
 * @info: Structure containing potential arguments, maintaining
 *        constant function prototype.
 * Return: Returns 0 on success, 1 on error.
 */
int manage_alias(info_t *info)
{
	int i;
	char *equals, *alias;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_single_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equals = _strchr(info->argv[i], '=');
		if (equals)
			add_alias(info, info->argv[i]);
		else
			print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
