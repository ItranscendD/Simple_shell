#include "shell.h"

/**
 * print_error_string - Prints the input string to the standard error.
 * @str: The string to be printed.
 *
 * Return: Always returns 0.
 */
void print_error_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		write_error_character(str[index]);
		index++;
	}
}

/**
 * write_error_character - Writes the character to the standard error.
 * @c: The character to be written.
 *
 * Return: On success, returns 1.
 * On error, errno is set appropriately, and -1 is returned.
 */
int write_error_character(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * write_to_file_descriptor - Writes the character to a given file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, errno is set appropriately, and -1 is returned.
 */
int write_to_file_descriptor(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * print_to_file_descriptor - Prints input str to given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_to_file_descriptor(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += write_to_file_descriptor(*str++, fd);
	}
	return (count);
}
