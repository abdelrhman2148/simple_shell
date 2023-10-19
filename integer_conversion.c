#include "shell.h"

/**
 * getIntegerLength - Get the length of an integer.
 * @n: The integer.
 * Return: The length of the integer.
*/
int getIntegerLength(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}

	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}
	return (length);
}

/**
 * intToString - Convert an integer to a string.
 * @n: The integer to convert.
 * Return: The string representation of the integer.
*/
char *intToString(int n)
{
	unsigned int n1;
	int length = getIntegerLength(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);
	buffer[length] = '\0';
	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}
	length--;
	do {
		buffer[length] = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	} while (n1 > 0);
	return (buffer);
}

/**
 * stringToInteger - Convert a string to an integer.
 * @s: The string to convert.
 * Return: The integer value.
*/
int stringToInteger(char *s)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, i;

	while (s[count] != '\0')
	{
		if (size > 0 && (s[count] < '0' || s[count] > '9'))
			break;
		if (s[count] == '-')
			sign *= -1;
		if (s[count] >= '0' && s[count] <= '9')
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}
	for (i = count - size; i < count; i++)
	{
		result = result + ((s[i] - '0') * multiplier);
		multiplier /= 10;
	}
	return (result * sign);
}
