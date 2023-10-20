#include "shell.h"

/**
 * _strlen - Calculates the length of a string
 * @s: The string for which the length is to be determined
 *
 * This function counts the number of characters in the given string until the
 * null-terminating character '\0' is encountered.
 *
 * @s: A pointer to the string.
 *
 * Return: The length of the string.
*/
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string to compare
 * @s2: The second string to compare
 *
 * This function compares two strings, 's1' and 's2', character by character
 * until a difference is found or until end of one of the strings is reached.
 * The comparison is case-sensitive.
 *
 * Return: An integer value that indicates the result of the comparison:
 *         - Negative if s1 < s2
 *         - Positive if s1 > s2
 *         - Zero if s1 is equal to s2
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
 * starts_with - Check if the given string starts with a specific substring.
 *
 * This function checks if the 'haystack' string starts substring.
 *
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: The address of the next character in 'haystack'
 * if 'needle' is found at the beginning, or NULL
 * if 'needle' is not present at the start of 'haystack'.
*/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - Concatenate two strings.
 *
 * This function concatenates the 'src' string to the end of the dest string.
 *
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: A pointer to the 'dest' buffer with 'src' appended to it.
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
