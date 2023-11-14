#include "shell.h"

/**
 * _myexit - Exit the shell
 * @info: The info structure
 *
 * Return: Always returns 0
 */
int _myexit(info_t *info)
{
	free_info(info, 1);
	exit(EXIT_SUCCESS);
}

/**
 * _mycd - Change directory
 * @info: The info structure
 *
 * Return: Always returns 0
 */
int _mycd(info_t *info)
{
	char *path = info->argv[1] ? info->argv[1] : _getenv(info, "HOME");

	if (!path)
	{
		print_error(info, "cd: HOME not set");
		return (0);
	}

	if (chdir(path) == -1)
	{
		print_error(info, "cd: can't cd to ");
		_puts(path);
		_putchar('\n');
	}

	return (0);
}

/**
 * _myhelp - Display help information
 * @info: The info structure
 *
 * Return: Always returns 0
 */
int _myhelp(info_t *info)
{
	(void)info;
	_puts("Simple Shell\n");
	_puts("Usage: Type commands and press Enter.\n");
	_puts("Built-in commands: exit, cd, help\n");
	return (0);
}
