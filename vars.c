#include "shell.h"

/**
 * is_chain - Check if a string is a command chain.
 * @info: Information struct containing relevant data.
 * @str: String to check.
 * @pos: Pointer to the current position in the command.
 * @chain_type: Type of command chain.
 * Return: 1 if the string is a command chain, 0 otherwise.
 */
int is_chain(info_t *info, char *str, size_t *pos, size_t chain_type)
{
	char *chain_op[] = {"||", "&&", ";", NULL};
	size_t len;

	if (!str || !info || !pos || chain_type >= CMD_CHAIN)
		return (0);

	len = strlen(chain_op[chain_type]);

	if (strncmp(str, chain_op[chain_type], len) == 0)
	{
		*pos += len;
		return (1);
	}

	return (0);
}

/**
 * check_chain - Check for command chaining.
 * @info: Information struct containing relevant data.
 * @str: String to check.
 * @i: Pointer to the current position in the string.
 * @chain_type: Type of command chain.
 * @token_len: Length of the current token.
 */
void check_chain(info_t *info, char *str, size_t chain_type, size_t token_len)
{
	size_t pos;

	pos = *i;

	if (is_chain(info, str + pos, &pos, chain_type))
	{
		info->cmd_buf_type = chain_type;
		info->cmd_buf = info->cmd_buf ? info->cmd_buf :
				(char **)malloc(sizeof(char *) * CMD_CHAIN);
		if (!info->cmd_buf)
			return;

		if (chain_type != CMD_NORM)
			strncat(info->cmd_buf, &str[*i], token_len);

		info->cmd_buf[chain_type] = NULL;
		*i += token_len + pos;
	}
}

/**
 * replace_alias - Replace aliases in a string.
 * @info: Information struct containing relevant data.
 * Return: 0 on success, -1 on failure.
 */
int replace_alias(info_t *info)
{
	list_t *node = info->alias;

	while (node)
	{
		if (starts_with(info->arg, node->str))
		{
			free(info->arg);
			info->arg = _strdup(&node->str[_strlen(node->str) + 1]);
			if (!info->arg)
				return (-1);
			return (0);
		}
		node = node->next;
	}

	return (0);
}

/**
 * replace_vars - Replace variables in a string.
 * @info: Information struct containing relevant data.
 * Return: 0 on success, -1 on failure.
 */
int replace_vars(info_t *info)
{
	size_t i = 0;

	if (!info->arg || info->arg[0] != '$')
		return (0);

	while (info->arg[i] == '$' || info->arg[i] == '\\')
		i++;

	if (_getenv(info, &info->arg[i]))
	{
		free(info->arg);
		info->arg = _strdup(_getenv(info, &info->arg[i]));
		if (!info->arg)
			return (-1);
	}

	return (0);
}

/**
 * replace_string - Replace a string in an array of strings.
 * @arr: Array of strings.
 * @to_replace: String to replace.
 * Return: 0 on success, -1 on failure.
 */
int replace_string(char **arr, char *to_replace)
{
	size_t i = 0;

	if (!arr || !to_replace)
		return (-1);

	while (arr[i])
	{
		if (starts_with(arr[i], to_replace))
		{
			free(arr[i]);
			arr[i] = _strdup(&to_replace[_strlen(to_replace) + 1]);
			if (!arr[i])
				return (-1);
			return (0);
		}
		i++;
	}

	return (0);
}
