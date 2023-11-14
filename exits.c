#include "shell.h"

/**
 * _myexit - Builtin command to exit the shell.
 * @info: Information struct containing potential arguments.
 * Return: Always 0.
 */
int _myexit(info_t *info)
{
	if (info->argc == 1)
	{
		clear_info(info);
		free_info(info, 1);
		exit(info->status);
	}

	if (_atoi(info->argv[1]) == -1)
	{
		print_error(info, "exit: Illegal number: ");
		_puts(info->argv[1]);
		_puts("\n");
		info->status = 2;
		return (info->status);
	}

	info->status = _atoi(info->argv[1]);
	clear_info(info);
	free_info(info, 1);
	exit(info->status);

	return (info->status);
}
