#include "shell.h"

/**
 * _strcpy - This copies a string
 * @dest: This is the destination of the copied string
 * @src: This is the source of the copied string
 *
 * Return: As a pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int d = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[d])
	{
		dest[d] = src[d];
		d++;
	}
	dest[d] = 0;
	return (dest);
}

/**
 * _strdup - This will duplicate a string
 * @str: This is the string to duplicate
 *
 * Return: As a pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - This will print an input string
 * @str: This is the string to be printed
 *
 * Return: As nothing
 */
void _puts(char *str)
{
	int d = 0;

	if (!str)
		return;
	while (str[d] != '\0')
	{
		_putchar(str[d]);
		d++;
	}
}

/**
 * _putchar - This will write the character c to stdout
 * @c: The character to print out
 *
 * Return: 1 On success.
 * On error, errno is set appropriately, -1 is returned.
 */
int _putchar(char c)
{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
		write(1, buf, d);
		d = 0;
	}
	if (c != BUF_FLUSH)
		buf[d++] = c;
	return (1);
}
