#include "shell.h"

/**
 * _strlen - The length of a string is returned
 * @s: This is the string whose length to check
 *
 * Return: As an integer length of the string
 */
int _strlen(char *s)
{
	int d = 0;

	if (!s)
		return (0);

	while (*s++)
		d++;
	return (d);
}

/**
 * _strcmp - will perform a lexicographic comparison of two strings.
 * @s1: This is the first string
 * @s2: This is the second string
 *
 * Return: Positive if s1 > s2, zero if s1 == s2, negative if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - will check if a needle starts with haystack
 * @haystack: This is the string to be searched
 * @needle: This is the substring to find
 *
 * Return: As the address of the next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This concatenates two strings
 * @dest: This is the destination buffer
 * @src: This is the source buffer
 *
 * Return: As a pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
