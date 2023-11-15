#include "shell.h"

/**
 * _strncpy - This copies a string
 * @dest: the destination string that will be copied to
 * @src: this is the source string
 * @n: this is the amount of characters copied
 * Return: this is the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int d, a;
	char *s = dest;

	d = 0;
	while (src[d] != '\0' && d < n - 1)
	{
		dest[d] = src[d];
		d++;
	}
	if (d < n)
	{
		a = d;
		while (d < n)
		{
			dest[a] = '\0';
			a++;
		}
	}
	return (s);
}

/**
 * _strncat - this will concatenate two strings
 * @dest: this is the first string
 * @src: this is the second string
 * @n: the maximum amount of bytes to be used
 * Return: this is the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int d, a;
	char *s = dest;

	d = 0;
	a = 0;
	while (dest[d] != '\0')
		d++;
	while (src[a] != '\0' && a < n)
	{
		dest[d] = src[a];
		d++;
		a++;
	}
	if (a < n)
		dest[d] = '\0';
	return (s);
}

/**
 * _strchr - this locates a character within a string
 * @s: this is the string to be parsed
 * @c: this is the character to be found
 * Return: (s) this is a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
