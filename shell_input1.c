#include "shell.h"

/**
 * get_input_line - 
 *
 * @i_eof: 
 * Return: 
*/
char *get_input_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);
	return (input);
}
