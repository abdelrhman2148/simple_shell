#include "shell.h"

/**
 * interactive - Check if the shell is running in interactive mode.
 * @info: Pointer to a struct that contains information about the shell.
 *
 * This function checks whether the shell is currently operating
 * in an interactive mode, meaning it can accept input
 * and provide output to the user via a terminal.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - Check if a character is a delimiter in a given delimiter string.
 * @c: The character to check.
 * @delim: The delimiter string to search within.
 *
 * This function iterates through the delimiter string and checks if the given
 * character 'c' matches any character in the delimiter string.
 * If a match is found, the fun returns 1, indicating that 'c' is a delimiter.
 * Otherwise, it returns 0, indicating that 'c' is not a delimiter.
 *
 * Return: 1 if 'c' is a delimiter, 0 if 'c' is not a delimiter.
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - Checks if a character is an alphabetic character
 * @c: The character to be checked
 *
 * This function takes a character 'c' as input and checks whether it is an
 * alphabetic character (a letter). It returns 1 if 'c' is an alphabetic
 * character (either uppercase or lowercase), and 0 otherwise.
 *
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
*/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted to an integer.
 *
 * Return: The converted integer. If there are no valid numbers
 * in the string, it returns 0.
*/
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
