#include "shell.h"

/**
 * is_cmd - will determine if a file is an executable command
 * @info: This is the info struct
 * @path: This is the path to the file
 *
 * Return: If true 1, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - This will duplicate characters
 * @pathstr: This is the PATH string
 * @start: This is the starting index
 * @stop: This is the stopping index
 *
 * Return: As a pointer to a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int d = 0, k = 0;

	for (k = 0, d = start; d < stop; d++)
		if (pathstr[d] != ':')
			buf[k++] = pathstr[d];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - This locates this cmd in the PATH string
 * @info: This is the info struct
 * @pathstr: This is the PATH string
 * @cmd: This is the cmd to find
 *
 * Return: As NULL or full path of cmd if found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int d = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[d] || pathstr[d] == ':')
		{
			path = dup_chars(pathstr, curr_pos, d);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[d])
				break;
			curr_pos = d;
		}
		d++;
	}
	return (NULL);
}
