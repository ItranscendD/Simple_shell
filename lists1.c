#include "shell.h"

/**
 * list_len - This will determine the length of linked list
 * @h: This is the pointer to the first node
 *
 * Return: Return as the size of the list
 */
size_t list_len(const list_t *h)
{
	size_t d = 0;

	while (h)
	{
		h = h->next;
		d++;
	}
	return (d);
}

/**
 * list_to_strings - will return an array of strs of the list->str
 * @head: This is the pointer to the first node
 *
 * Return: Return as an array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t d = list_len(head), a;
	char **strs;
	char *str;

	if (!head || !d)
		return (NULL);
	strs = malloc(sizeof(char *) * (d + 1));
	if (!strs)
		return (NULL);
	for (d = 0; node; node = node->next, d++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (a = 0; a < d; a++)
				free(strs[a]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[d] = str;
	}
	strs[d] = NULL;
	return (strs);
}

/**
 * print_list - will print all elements of a list_t linked list
 * @h: This is the pointer to the first node
 *
 * Return: Return as the size of the list
 */
size_t print_list(const list_t *h)
{
	size_t d = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		d++;
	}
	return (d);
}

/**
 * node_starts_with - Will return node whose string starts with prefix
 * @node: This is the pointer to the list head
 * @prefix: This is the string to match
 * @c: The next character after prefix to match
 *
 * Return: Return as the match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This will get the index of a node
 * @head: This is the pointer to the list head
 * @node: This is the pointer to the node
 *
 * Return: Return as -1 or the index of the node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t d = 0;

	while (head)
	{
		if (head == node)
			return (d);
		head = head->next;
		d++;
	}
	return (-1);
}
