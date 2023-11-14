#include "shell.h"

/**
 * get_input - Get user input from stdin.
 * @info: Information struct containing relevant data.
 * Return: Number of bytes read, or -1 on failure.
 */
ssize_t get_input(info_t *info)
{
	ssize_t bytes_read;

	if (isatty(STDIN_FILENO))
		_puts("$ ");

	bytes_read = _getline(info, &(info->arg), &(info->linecount_flag));

	if (bytes_read == -1)
	{
		if (isatty(STDIN_FILENO))
			_puts("\n");
		print_error(info, "Error reading from stdin");
	}

	return (bytes_read);
}

/**
 * _getline - Custom implementation of the getline function.
 * @info: Information struct containing relevant data.
 * @line: Address of the buffer to store the line.
 * @n: Address of the variable to store the size.
 * Return: Number of bytes read, or -1 on failure.
 */
int _getline(info_t *info, char **line, size_t *n)
{
	ssize_t bytes_read;
	size_t len = 0;

#if USE_GETLINE
	bytes_read = getline(line, n, stdin);
#else
	bytes_read = getline(line, &len, stdin);
	*n = len;
#endif

	if (bytes_read == -1)
		return (-1);

	if (*line && bytes_read > 0 && (*line)[bytes_read - 1] == '\n')
	{
		(*line)[bytes_read - 1] = '\0';
		info->line_count++;
	}

	return (bytes_read);
}

/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C).
 * @sig_num: Signal number.
 */
void sigintHandler(int sig_num)
{
	(void)sig_num;
	_putchar('\n');
	if (isatty(STDIN_FILENO))
		_puts("$ ");
	fflush(stdout);
}
