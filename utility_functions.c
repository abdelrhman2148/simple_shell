#include "shell.h"

/**
 * convert_string_to_integer - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer if successful, -1 on error.
*/
int convert_string_to_integer(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - Print an error message to standard error (stderr).
 * @info: The parameter and return info struct.
 * @error_string: String containing the specified error type.
 *
 * Return: Nothing.
*/
void print_error_message(info_t *info, char *error_string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * print_decimal - Print a decimal (integer) number (base 10).
 * @input: The input integer.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
*/
int print_decimal(int input, int fd)
{
	int (*print_char)(char) = write_to_fd;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		print_char = write_to_fd;
	if (input < 0)
	{
		absolute_value = -input;
		print_char('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;
	return (count);
}

/**
 * convert_integer_to_string - Convert an integer to a string.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: A string representation of the integer.
*/
char *convert_integer_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - Replace the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Always 0.
*/
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
