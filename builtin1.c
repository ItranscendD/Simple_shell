#include "shell.h"

/**
 * _myhistory - Display command history
 * @info: The info structure
 *
 * Return: Always returns 0
 */
int _myhistory(info_t *info)
{
	list_t *current = info->history;
	int count = 1;

	while (current)
	{
		print_d(count, 1);
		_putchar(' ');
		_puts(current->str);
		_putchar('\n');
		current = current->next;
		count++;
	}

	return (0);
}

/**
 * _myalias - Display or set command aliases
 * @info: The info structure
 *
 * Return: Always returns 0
 */
int _myalias(info_t *info)
{
	(void)info;
	_puts("Alias functionality not implemented\n");
	return (0);
}
