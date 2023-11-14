#include "shell.h"

/**
 * list_len - Count the number of elements in a linked list.
 * @h: Pointer to the head of the list.
 * Return: Number of elements in the list.
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		count++;
		h = h->next;
	}
	return (count);
}

/**
 * list_to_strings - Convert a linked list to an array of strings.
 * @head: Pointer to the head of the list.
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	size_t len = list_len(head);
	char **strings = malloc((len + 1) * sizeof(char *));
	size_t i;

	if (!strings)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		strings[i] = strdup(head->str);
		if (!strings[i])
		{
			for (i = 0; i < len; i++)
				free(strings[i]);
			free(strings);
			return (NULL);
		}
		head = head->next;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * print_list - Print the elements of a linked list.
 * @h: Pointer to the head of the list.
 * Return: Number of nodes in the list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str);
		_putchar('\n');
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Find node string in list that starts with prefix.
 * @head: Pointer to the head of the list.
 * @prefix: Prefix to search for.
 * @c: Comparison mode: 0 for an exact match, -1 for a prefix match.
 * Return: Pointer to the found node or NULL if not found.
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
	while (head)
	{
		if (c == -1 && starts_with(head->str, prefix))
			return (head);
		else if (c == 0 && strcmp(head->str, prefix) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a node in a linked list.
 * @head: Pointer to the head of the list.
 * @node: Node to find the index of.
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	ssize_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
