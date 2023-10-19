#include "shell.h"
/**
 * get_input_line - Reads a line of input from the standard input.
 *
 * @i_eof: Pointer to an integer that will be set to 1 if EOF is reached,
 *                                                             0 otherwise.
 *
 * Return: A pointer to a dynamically allocated string.
 */
char *get_input_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);
	return (input);
}
