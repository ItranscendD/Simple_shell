#include "shell.h"

/**
 * add_node - Add a node at the beginning of a linked list.
 * @head: Pointer to the head of the list.
 * @str: String to be added.
 * @num: Number associated with the string.
 * Return: Pointer to the new node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->str = strdup(str);
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}

	new_node->num = num;
	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Add a node at the end of a linked list.
 * @head: Pointer to the head of the list.
 * @str: String to be added.
 * @num: Number associated with the string.
 * Return: Pointer to the new node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->str = strdup(str);
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}

	new_node->num = num;
	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
	}
	else
	{
		list_t *temp = *head;

		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - Print the strings in a linked list.
 * @h: Pointer to the head of the list.
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		printf("%s\n", h->str);
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - Delete a node at a given index in a linked list.
 * @head: Pointer to the head of the list.
 * @index: Index of the node to be deleted.
 * Return: 1 if successful, -1 if failed.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (-1);

	if (index == 0)
	{
		list_t *temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	list_t *prev = NULL;
	list_t *current = *head;
	unsigned int i;

	for (i = 0; i < index && current; i++)
	{
		prev = current;
		current = current->next;
	}

	if (i != index)
		return (-1);

	if (prev)
		prev->next = current->next;
	else
		*head = current->next;

	free(current->str);
	free(current);
	return (1);
}

/**
 * free_list - Free a linked list.
 * @head: Pointer to the head of the list.
 */
void free_list(list_t **head)
{
	if (!head || !*head)
		return;

	list_t *current = *head;
	list_t *next;

	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}

	*head = NULL;
}
