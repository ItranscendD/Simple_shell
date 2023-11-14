/**
 * hsh - Main function for the shell loop.
 * @info: Structure containing potential arguments.
 * @av: Array of strings generated from arg.
 * Return: Always 0.
 */
int hsh(info_t *info, char **av)
{
	(void)av; /* unused parameter */
	info->readfd = STDIN_FILENO;

	while (1)
	{
		if (isatty(STDIN_FILENO)) /* Interactive mode */
			_puts("$ ");
		if (get_input(info) == -1)
			break;
		if (info->arg && *(info->arg))
		{
			set_info(info, av);
			find_builtin(info);
			replace_alias(info);
			replace_vars(info);
			if (info->argv && *(info->argv))
				fork_cmd(info);
			free_info(info, 1);
		}
	}

	if (isatty(STDIN_FILENO))
		_puts("\n");

	free_info(info, 1);
	return (0);
}
