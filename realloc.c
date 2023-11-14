#include "shell.h"

/**
 * _memset - Fill memory with a constant byte.
 * @s: Memory area.
 * @b: Constant byte.
 * @n: Number of bytes to fill.
 * Return: Pointer to the memory area.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	if (!s)
	{
		print_error(NULL, "Error in _memset: NULL pointer");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * ffree - Free a double pointer and set to NULL.
 * @arr: Double pointer to be freed.
 */
void ffree(char **arr)
{
	if (!arr || !*arr)
	{
		print_error(NULL, "Error in ffree: NULL pointer");
		exit(EXIT_FAILURE);
	}

	free(*arr);
	*arr = NULL;
}

/**
 * _realloc - Reallocate memory block using malloc and free.
 * @ptr: Pointer to the previously allocated memory.
 * @old_size: Size of the allocated space for ptr.
 * @new_size: New size in bytes to be allocated.
 * Return: Pointer to the newly allocated memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (!ptr)
		return (malloc(new_size));

	if (new_size <= old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		print_error(NULL, "Error in _realloc: Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	_memset(new_ptr, 0, new_size);

	if (!memcpy(new_ptr, ptr, old_size))
	{
		print_error(NULL, "Error in _realloc: Memory copy failed");
		exit(EXIT_FAILURE);
	}

	free(ptr);

	return (new_ptr);
}
