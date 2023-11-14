#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: Destination buffer.
 * @src: Source string.
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while ((dest[i] = src[i]) != '\0')
		i++;

	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: String to duplicate.
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	char *dup_str;
	int len, i;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	dup_str = malloc((len + 1) * sizeof(char));
	if (dup_str == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup_str[i] = str[i];

	return (dup_str);
}

/**
 * _puts - Prints a string to standard output.
 * @str: String to print.
 */
void _puts(char *str)
{
	while (*str)
		_putchar(*str++);
}

/**
 * _putchar - Writes a character to standard output.
 * @c: Character to write.
 * Return: On success, the number of characters written.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
