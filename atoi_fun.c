#include "shell.h"

/**
 * check_interactive_mode - Check if the shell is in interactive mode.
 * @info: Pointer to info_t struct.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
*/
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 * Return: 1 if the character is a delimiter, 0 if not.
*/
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * is_alpha - Check if a character is alphabetic.
 * @c: The character to check.
 * Return: 1 if the character is alphabetic, 0 if not.
*/
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - Convert a string to an integer.
 * @s: The string to be converted.
 * Return: The converted integer, or 0 if no numbers in the string.
*/
int string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		} else if (flag == 1)
		{
			flag = 2;
		}
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
