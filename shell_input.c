#include "shell.h"
/**
 * load_line - Load a line of input into a dynamic buffer.
 * @lineptr: A pointer to a pointer that will hold the line.
 * @n: A pointer to the size of the buffer.
 * @buffer: A character array to store the line temporarily.
 * @length: The length of the line to load.
*/
void load_line(char **lineptr, size_t *n, char *buffer, size_t length)
{
	if (*lineptr == NULL)
	{
		if (length > BUFSIZE)
			*n = length;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < length)
	{
		if (length > BUFSIZE)
			*n = length;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * custom_get_line - Custom implementation of getting
 *                          a line of input from a stream.
 * @lineptr: A pointer to a pointer that will hold the line.
 * @n: A pointer to the size of the buffer.
 * @stream: The input stream.
 *
 * Return: The number of characters read, or -1 on error.
*/
ssize_t custom_get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		flush(stream);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	load_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
