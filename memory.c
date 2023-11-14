#include "shell.h"

/**
 * _memset - Fills the first n bytes of the memory area pointed to by s
 *           with the constant byte b
 * @s: A pointer to the memory area to be filled.
 * @b: The character to fill the memory area with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	if (s == NULL)
		return (NULL);

	for (unsigned int i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * ffree - Frees an array of strings and sets the pointer to NULL
 * @arr: Double pointer to be freed.
 */
void ffree(char **arr)
{
	if (arr == NULL || *arr == NULL)
		return;

	for (int i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr);
	arr = NULL;
}

/**
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: Pointer to the memory previously allocated with a call to malloc
 * @old_size: Size of the allocated space for ptr
 * @new_size: New size for the memory block
 *
 * Return: A pointer to the newly allocated memory, or NULL if it fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);

	if (new_ptr == NULL)
		return (NULL);

	_memset(new_ptr, 0, new_size);

	if (old_size < new_size)
		_memcpy(new_ptr, ptr, old_size);
	else
		_memcpy(new_ptr, ptr, new_size);

	free(ptr);

	return (new_ptr);
}

/**
 * bfree - Frees a pointer (memory block) and sets the pointer to NULL
 * @ptr: Pointer to be freed.
 *
 * Return: Always 1
 */
int bfree(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return (1);

	free(*ptr);
	*ptr = NULL;

	return (1);
}
