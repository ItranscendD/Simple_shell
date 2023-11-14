#include "shell.h"

/**
 * _erratoi - Convert a string to an integer, handling errors.
 * @str: String to be converted.
 * Return: Converted integer or -1 on error.
 */
int _erratoi(char *str)
{
int result = 0;

if (*s == '+')
		s++;  /* TODO: why is main return 255? */
	for (d = 0;  s[d] != '\0'; d++)
	{
		if (s[d] >= '0' && s[d] <= '9')
		{
			result *= 10;
			result += (s[d] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
return (result);
}

/**
 * print_error - Print an error message.
 * @info: Information struct containing relevant data.
 * @msg: Error message to be printed.
 */
void print_error(info_t *info, char *msg)
{
_eputs(info->fname);
_eputs(": ");
_eputchar(info->line_count + '0');
_eputs(": ");
_eputs(msg);
}

/**
 * print_d - Print a decimal number.
 * @num: Number to be printed.
 * @fd: File descriptor.
 * Return: Number of digits printed.
 */
int print_d(int num, int fd)
{
int (*__putchar)(char) = _putchar;
	int d, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (d = 1000000000; d > 1; d /= 10)
	{
		if (_abs_ / d)
		{
			__putchar('0' + current / d);
			count++;
		}
		current %= d;
	}
	__putchar('0' + current);
	count++;

return (count);
}

/**
 * convert_number - Convert a number to a string.
 * @num: Number to be converted.
 * @flags: Conversion flags.
 * @base: Base for conversion.
 * Return: Converted string.
 */
char *convert_number(long int num, int flags, int base)

{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Remove comments from a string.
 * @str: String to be processed.
 */
void remove_comments(char *str)
{
int d;

	for (d = 0; buf[d] != '\0'; d++)
		if (buf[d] == '#' && (!d || buf[d - 1] == ' '))
		{
			buf[d] = '\0';
			break;
		}
}
