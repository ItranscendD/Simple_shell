#include "shell.h"

/**
 * bfree - This will free up a pointer and NULL the address
 * @ptr: The pointer address to free
 *
 * Return: If freed 1, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
