#include "shell.h"

/**
 * get_history_file - will get the history file in the code
 * @info: this is the parameter struct
 *
 * Return: this is the allocated string that contains the history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - will append to an existing file or creates a new file
 * @info: this is the parameter struct
 *
 * Return: if successful, return as 1, if failed -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - will read the history from the file
 * @info: This is the parameter struct
 *
 * Return: on success histcount ,otherwise 0
 */
int read_history(info_t *info)
{
	int d, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (d = 0; d < fsize; d++)
		if (buf[d] == '\n')
		{
			buf[d] = 0;
			build_history_list(info, buf + last, linecount++);
			last = d + 1;
		}
	if (last != d)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - This adds an entry to a history linked list
 * @info: this is a Structure containing potential arguments.
 * it is Used to maintain constant function prototype.
 * @buf: This is the buffer
 * @linecount: This is the history linecount, know as histcount
 *
 * Return: will Always be 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - after changes, renumber the history linked list
 * @info: Structure containing potential arguments.
 * it is Used to maintain constant function prototype.
 *
 * Return: on return, new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int d = 0;

	while (node)
	{
		node->num = d++;
		node = node->next;
	}
	return (info->histcount = d);
}
