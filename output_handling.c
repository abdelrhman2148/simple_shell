#include "shell.h"

/**
 * print_error_message - Print an error message to standard error (stderr).
 * @str: The error message to be printed.
 *
 * Return: Nothing.
*/
void print_error_message(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_stderr(str[i]);
		i++;
	}
}

/**
 * write_stderr - Write a character to standard error (stderr).
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set.
*/
int write_stderr(char c)
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
 * write_to_fd - Write a character to a given file descriptor (fd).
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set.
*/
int write_to_fd(char c, int fd)
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
 * print_to_fd - Print an input string to a given file descriptor (fd).
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
*/
int print_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_to_fd(*str++, fd);
	}
	return (i);
}
