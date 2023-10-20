#include "shell.h"

/**
 * _strncpy - Copies a portion of a source string to a destination string.
 *
 * This function copies the first 'n' characters from the source string 'src' to
 * the destination string 'dest'. It ensures that the destination string is null-terminated
 * and has a maximum length of 'n'.
 *
 * @param dest: The destination string where the copied characters will be stored.
 * @param src: The source string from which characters are copied.
 * @param n: The maximum number of characters to copy from src.
 *
 * @return: A pointer to the destination string 'dest'.
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenate two strings with a maximum byte limit
 * @dest: The destination string where the concatenation occurs
 * @src: The source string to be appended to dest
 * @n: The maximum number of bytes from src to concatenate
 *
 * This function concatenates the 'src' string to the 'dest' string, ensuring that
 * no more than 'n' bytes from 'src' are appended to 'dest'. It stops when the
 * 'n' bytes are reached or when the end of 'src' is reached, whichever comes first.
 *
 * Return: A pointer to the concatenated string (same as 'dest').
*/
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
/**
 * _strchr - Locates the first occurrence of a character in a string
 * @s: The string to be searched
 * @c: The character to find
 *
 * This function searches for the first occurrence of the character 'c' in the
 * string 's' and returns a pointer to the memory location where it is found.
 *
 * Return: A pointer to the first occurrence of 'c' in 's'
 *                               or NULL if 'c' is not found.
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
