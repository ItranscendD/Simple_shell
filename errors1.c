#include "shell.h"

/**
 * custom_str_to_int - Converts string to integer with error handling.
 * @s: The string to be converted.
 *
 * Return: If no num in string, 0. -1 on error, converted num otherwise.
 */
int custom_str_to_int(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_error - Prints a custom error message.
 * @info: Return info structure.
 * @error_str: The specified error type contained in this string.
 *
 * Return: void
 */
void print_custom_error(info_t *info, char *error_str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_str);
}

/**
 * print_decimal - Prints a decimal (integer) number.
 * @input: The input number.
 * @fd: Filedescriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int (*write_char)(char) = _putchar;
	int index, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		write_char = _eputchar;

	if (input < 0)
	{
		absolute = -input;
		write_char('-');
		count++;
	}
	else
		absolute = input;

	current = absolute;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absolute / index)
		{
			write_char('0' + current / index);
			count++;
		}
		current %= index;
	}
	write_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string in the given base.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: A string representing the converted number.
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *char_array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

#define CHAR_ARRAY_LOWER "0123456789abcdef"
#define CHAR_ARRAY_UPPER "0123456789ABCDEF"
	char_array = flags & CONVERT_LOWERCASE ? CHAR_ARRAY_LOWER : CHAR_ARRAY_UPPER;
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = char_array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * eliminate_comments - Replaces the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 *
 * Return: Always returns 0.
 */
void eliminate_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
