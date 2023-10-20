#include "shell.h"

/**
 * _erratoi - Convert a string to an integer with error handling
 * @s: The string to be converted to an integer
 * 
 * This function takes a string 's' as input and converts it into an integer.
 * It performs error checking to ensure the conversion is valid.
 * 
 * @return: The converted integer if successful, -1 on error.
*/
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
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
 * print_error - Prints an error message to the standard error stream.
 * @info: A pointer to the info_t struct containing program information.
 * @estr: A string containing the specified error message.
 * 
 * This function is responsible for printing an error message to the standard
 * error stream. It includes information about the file name, line number,
 * and the error message itself, making it easier to identify and debug errors.
*/
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - This function prints a decimal (integer) number in base 10.
 * @input: The integer to be printed.
 * @fd: The file descriptor where the output is written.
 *
 * This function takes an integer 'input' and prints it as a decimal number.
 * If 'fd' is set to STDERR_FILENO, error output is used. It handles negative
 * numbers correctly and returns the number of characters printed.
 *
 * Returns: The number of characters printed.
*/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
/**
 * convert_number - Converts a long integer to a string represented
 * @num: The number to be converted.
 * @base: The base in which the conversion should be done.
 * @flags: Flags that control the conversion process.
 *
 * This function takes a long integer 'num' and converts it into
 *                   a string representation in the specified 'base'.
 * It considers the 'flags' to determine the conversion behavior
 *                                    such as handling unsigned numbers.
 *
 * Return: A pointer to the resulting string.
*/
char *convert_number(long int num, int base, int flags)
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

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance
 *               of '#' with a null character ('\0'.)
 * @buf: The address of the string to modify
 *
 * This function scans the input string 'buf' and if it finds
 *           the character '#', it replaces the first occurrence
 *                of '#' with a null character.
 * This effectively removes any text following the '#' symbol in 'buf'.
 *
 * Returns: Always 0.
*/
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
