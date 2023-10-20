#include "shell.h"
/**
 * _eputs - Prints a string to the standard output.
 * @str: The string to be printed.
 *
 * This function takes a string as input and prints it to the standard output.
 * If the input string is NULL, this function does nothing. It iterates through
 * the characters of the string and prints each character using the _eputchar
 * function until the null-terminating character '\0' is encountered.
 *
 * @str: A pointer to the string to be printed.
*/
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes a character to the standard error stream.
 *
 * This function writes the character 'c' to the standard error stream.
 * If 'c' is equal to BUF_FLUSH or the internal buffer is full, it flushes the
 * buffer to stderr and resets it.
 *
 * @c: The character to be written to stderr.
 *
 * Return: On success, it returns 1. On error, -1 is returned,
 * and errno is set appropriately.
*/
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes a character to the given file descriptor.
 *
 * This function writes a single character to the specified file descriptor.
 * It uses a buffer to optimize write operations
 * flushing the buffer when necessary.
 *
 * @c: The character to write.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1 is returned. On error, -1 is returned
 * and errno is set appropriately.
*/
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Prints an input string to a specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function takes a string 'str' and writes it to the file descriptor.
 * It calculates and returns the number of characters written.
 *
 * Return: The number of characters successfully written to 'fd'.
*/
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
