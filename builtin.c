#include "shell.h"

/**
 * _custom_exit - This will exit the shell uniquely.
 * @info: this contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Will exit with a given exit status.
 * "exit" = (0) if info.argv[0] is not empty!
 */
int _custom_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = _custom_erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_custom_eputs(info->argv[1]);
			_custom_eputchar('\n');
			return (1);
		}
		info->err_num = _custom_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _custom_cd - This changes the directory of the current process.
 * @info: this contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always returns 0.
 */
int _custom_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _custom_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = _custom_chdir(
				(dir = _custom_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = _custom_chdir(dir);
	}
	else if (_custom_strcmp(info->argv[1], "-") == 0)
	{
		if (!_custom_getenv(info, "OLDPWD="))
		{
			_custom_puts(s);
			_custom_putchar('\n');
			return (1);
		}
		_custom_puts(_custom_getenv(info, "OLDPWD=")), _custom_putchar('\n');
		chdir_ret = _custom_chdir(
			(dir = _custom_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = _custom_chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_custom_eputs(info->argv[1]), _custom_eputchar('\n');
	}
	else
	{
		_custom_setenv(info, "OLDPWD", _custom_getenv(info, "PWD="));
		_custom_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _custom_help - This will print a custom help message.
 * @info: this contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always returns 0.
 */
int _custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_custom_puts("custom help call works. Function not yet implemented \n");
	if (0)
		_custom_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
