#include "shell.h"

/**
 * input_buf - This will buffer chained commands
 * @info: the parameter struct
 * @buf: buffer address
 * @len: len variable address
 *
 * Return: it will return bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if buffer is emptied, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - this gets a line minus the newline
 * @info: this is the parameter structure
 *
 * Return: it will return bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t d, a, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* commands are left in the chain buffer */
	{
		a = d; /* init new iterator to current buf position */
		p = buf + d; /* get pointer for return */

		check_chain(info, buf, &a, d, len);
		while (a < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &a))
				break;
			a++;
		}

		d = a + 1; /* increment past nulled ';'' */
		if (d >= len) /* reached end of buffer? */
		{
			d = len = 0; /* reset the position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass pointer to current command position */
		return (_strlen(p)); /* return the length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - buffer is read
 * @info: this is the parameter struct
 * @buf: buffer address
 * @d: the size
 *
 * Return: will return as r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *d)
{
	ssize_t r = 0;

	if (*d)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*d = r;
	return (r);
}

/**
 * _getline - this will get the next line of input from STDIN
 * @info: this is the parameter struct
 * @ptr: preallocated or NULL, the address of pointer to buffer,
 * @length: this is the size of preallocated ptr buffer, if it is not NULL
 *
 * Return: returns as s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t d, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (d == len)
		d = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + d, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + d, k - d);
	else
		_strncpy(new_p, buf + d, k - d + 1);

	s += k - d;
	d = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - will block ctrl-C
 * @sig_num: signal number
 *
 * Return: return void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
