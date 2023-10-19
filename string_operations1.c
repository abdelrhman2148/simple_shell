#include "shell.h"

/**
 * stringDuplicate - Duplicate a string.
 * @s: The string to duplicate.
 * Return: The duplicated string.
*/
char *stringDuplicate(const char *s)
{
	char *new;
	size_t len;

	len = stringLength(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	stringCopy(new, s);
	return (new);
}

/**
 * stringLength - Get the length of a string.
 * @s: The string to measure.
 * Return: The length of the string.
*/
int stringLength(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * compareCharacters - Compare characters in two strings.
 * @str: The string to compare.
 * @delim: The delimiter string.
 * Return: 1 if all characters in str are in delim, 0 otherwise.
*/
int compareCharacters(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * stringTokenize - Tokenize a string using a delimiter.
 * @str: The string to tokenize.
 * @delim: The delimiter string.
 * Return: A pointer to the next token, or NULL if no more tokens.
*/
char *stringTokenize(char str[], const char *delim)
{
	static char *splitted, *strEnd;
	char *strStart;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (compareCharacters(str, delim))
			return (NULL);
		splitted = str;
		i = stringLength(str);
		strEnd = &str[i];
	}
	strStart = splitted;
	if (strStart == strEnd)
		return (NULL);
	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != strStart)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == strStart)
					strStart++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (strStart);
}

/**
 * isStringDigit - Check if a string consists of only digits.
 * @s: The string to check.
 * Return: 1 if the string consists of only digits, 0 otherwise.
*/
int isStringDigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}
