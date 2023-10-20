#include "shell.h"

/**
 * copy_string - Copy a string from source to destination.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @max_characters: The maximum number of characters to be copied.
 *
 * Return: The concatenated string.
*/
char *copy_string(char *destination, char *source, int max_characters)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < max_characters - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < max_characters)
	{
		j = i;
		while (j < max_characters)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * concatenate_strings - Concatenate two strings.
 * @first: The first string.
 * @second: The second string.
 * @max_characters: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
*/
char *concatenate_strings(char *first, char *second, int max_characters)
{
	int i, j;
	char *result = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (second[j] != '\0' && j < max_characters)
	{
		first[i] = second[j];
		i++;
		j++;
	}
	if (j < max_characters)
		first[i] = '\0';
	return (result);
}

/**
 * find_character - Locate a character in a string.
 * @string: The string to be searched.
 * @character: The character to look for.
 *
 * Return: A pointer to the first occurrence, or NULL if not found.
*/
char *find_character(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}
