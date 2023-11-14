#include "shell.h"

int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	info_t info = INFO_INIT;

	if (argc > 1)
	{
		if (read_history(&info) == -1)
			perror(get_history_file(&info));
		_myexit(&info);
	}

	signal(SIGINT, sigintHandler);
	set_info(&info, argv);

	if (isatty(STDIN_FILENO))
		interactive(&info);
	else
	{
		while (getline(&line, &len, stdin) != -1)
		{
			if (line[0] != '\n')
				hsh(&info, &line);
		}
	}

	if (line)
		free(line);
	free_info(&info, 0);

	return (info.status);
}
