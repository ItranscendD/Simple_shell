#include "shell.h"

/**
 * _memset - This will fill memory with a constant byte
 * @s: This is the pointer to the memory area
 * @b: This is the byte to fill *s with
 * @n: This is the amount of bytes to be filled
 *
 * Return: As (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int d;

	for (d = 0; d < n; d++)
		s[d] = b;
	return (s);
}

/**
 * ffree - This will free up a string of strings
 * @pp: This is the string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - A block of memory will be reallocated
 * @ptr: This is the pointer to the previous malloc'ated block
 * @old_size: This is the byte size of the previous block
 * @new_size: This is the byte size of the new block
 *
 * Return: As a pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
