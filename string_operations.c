#include "shell.h"

/**
 * stringConcatenation - Concatenate two strings.
 * @dest: The destination string.
 * @src: The source string to append.
 * Return: The concatenated string.
*/
char *stringConcatenation(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * stringCopy - Copy a string to another.
 * @dest: The destination string.
 * @src: The source string to copy.
 * Return: The copied string.
*/
char *stringCopy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';
	return (dest);
}

/**
 * stringCompare - Compare two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if the strings are equal, a positive value if s1 > s2, a negative value if s1 < s2.
*/
int stringCompare(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * stringFindCharacter - Find the first occurrence of a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 * Return: A pointer to the first occurrence of the character, or NULL if not found.
*/
char *stringFindCharacter(char *s, char c)
{
	unsigned int i = 0;

	for (; s[i] != '\0'; i++)
		if (s[i] == c)
			return (s + i);
	if (s[i] == c)
		return (s + i);
	return (NULL);
}

/**
 * stringSpan - Get the length of the initial segment of a string that consists of only characters in another string.
 * @s: The string to examine.
 * @accept: The string containing characters to search for.
 * Return: The length of the initial segment.
*/
int stringSpan(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; s[i] != '\0'; i++)
	{
		bool = 1;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
