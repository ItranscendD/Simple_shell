#include "shell.h"

/**
 * is_chain - This will test if the current char in
 * buffer is a chain delimiter
 * @info: This is the parameter struct
 * @buf: This is the char buffer
 * @p: This is the address of the current position in buf
 *
 * Return: 0, otherwise 1 if chain delimiter
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - checks if chaining should continue
 * based on the last status
 * @info: This is the parameter struct
 * @buf: This is the char buffer
 * @p: This is the address of the current position in buf
 * @d: This is the starting position in buf
 * @len: This is the length of buf
 *
 * Return: as Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t d, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[d] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[d] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * replace_alias - Aliases in the tokenized string are replaced
 * @info: This is the parameter struct
 *
 * Return: as 0, otherwise 1 if replaced
 */
int replace_alias(info_t *info)
{
	int d;
	list_t *node;
	char *p;

	for (d = 0; d < 10; d++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - This will replace vars in the tokenized string
 * @info: This is the parameter struct
 *
 * Return: as 1 if replaced, otherwise 0
 */
int replace_vars(info_t *info)
{
	int d = 0;
	list_t *node;

	for (d = 0; info->argv[d]; d++)
	{
		if (info->argv[d][0] != '$' || !info->argv[d][1])
			continue;

		if (!_strcmp(info->argv[d], "$?"))
		{
			replace_string(&(info->argv[d]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[d], "$$"))
		{
			replace_string(&(info->argv[d]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[d][1], '=');
		if (node)
		{
			replace_string(&(info->argv[d]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[d], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - This will replace the string
 * @old: This is the address of the old string
 * @new: This is the new string
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
