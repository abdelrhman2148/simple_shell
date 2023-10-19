#include "shell.h"

/**
 * countRepeatedChar - Count the number of repeated characters at the beginning of a string.
 * @input: The input string.
 * @i: The current index in the string.
 * Return: The number of repeated characters.
*/
int countRepeatedChar(const char *input, int i)
{
	if (input[i - 1] == input[i])
		return countRepeatedChar(input, i + 1);
	return (i);
}

/**
 * findSyntaxError - Find syntax errors in the input string.
 * @input: The input string.
 * @i: The current index in the string.
 * @last: The last character processed.
 * Return: The index of the syntax error, or 0 if none is found.
*/
int findSyntaxError(const char *input, int i, char last)
{
	int count = 0;

	if (input[i] == '\0')
		return (0);
	if (input[i] == ' ' || input[i] == '\t')
		return findSyntaxError(input, i + 1, last);
	if (input[i] == ';')
	{
		if (last == '|' || last == '&' || last == ';')
			return (i);
	}
	if (input[i] == '|')
	{
		if (last == ';' || last == '&')
			return (i);
		if (last == '|')
		{
			count = countRepeatedChar(input, i);
			if (count == 0 || count > 1)
				return (i);
		}
	}
	if (input[i] == '&')
	{
		if (last == ';' || last == '|')
			return (i);
		if (last == '&')
		{
			count = countRepeatedChar(input, i);
			if (count == 0 || count > 1)
				return (i);
		}
	}
	return (findSyntaxError(input, i + 1, input[i]));
}

/**
 * findFirstNonSpecialChar - Find the index of the first non-special character in the input string.
 * @input: The input string.
 * @i: A pointer to store the index of the first non-special character.
 * Return: 0 if a valid character is found, -1 if a syntax error is found.
*/
int findFirstNonSpecialChar(const char *input, int *i)
{
	for (*i = 0; input[*i]; (*i)++)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * printSyntaxError - Print a syntax error message to stderr.
 * @datash: The data_shell structure.
 * @input: The input string.
 * @i: The index of the error.
*/
void printSyntaxError(data_shell *datash, const char *input, int i)
{
	const char *messages[] = {";", "|", "||", "&", "&&"};
	char *error, *counter;
	int length;
	int messageIndex = 0;

	if (input[i] == ';')
	{
		if (i > 0 && input[i - 1] == ';')
			messageIndex = 2;
		else
			messageIndex = 0;
	}
	else if (input[i] == '|')
	{
		if (i > 0 && input[i - 1] == '|')
			messageIndex = 2;
		else
			messageIndex = 1;
	}
	else if (input[i] == '&')
	{
		if (i > 0 && input[i - 1] == '&')
			messageIndex = 2;
		else
			messageIndex = 3;
	}
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(messages[messageIndex]) + 17;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, messages[messageIndex]);
	_strcat(error, "\" unexpected\n");
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * checkSyntaxError - Check for syntax errors in the input string.
 * @datash: The data_shell structure.
 * @input: The input string.
 * Return: 1 if a syntax error is found, 0 otherwise.
*/
int checkSyntaxError(data_shell *datash, const char *input)
{
	int i, begin = 0;
	int f_char = findFirstNonSpecialChar(input, &begin);

	if (f_char == -1)
	{
		printSyntaxError(datash, input, begin);
		return (1);
	}
	i = findSyntaxError(input, begin, input[begin]);
	
	if (i != 0)
	{
		printSyntaxError(datash, input, begin + i);
		return (1);
	}
	return (0);
}
