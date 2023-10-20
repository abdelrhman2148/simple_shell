/**
 * string_copy - Copies a source string to a destination.
 * @destination: The destination buffer.
 * @source: The source string to copy from.
 *
 * Return: A pointer to the destination buffer.
*/
char *string_copy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
	{
		return (destination);
	}
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (destination);
}

/**
 * string_duplicate - Duplicates a source string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
*/
char *string_duplicate(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		length++;
	}
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
	{
		return (NULL);
	}
	for (length++; length--;)
	{
		duplicate[length] = *--str;
	}
	return (duplicate);
}

/**
 * string_print - Prints an input string to stdout.
 * @str: The string to be printed.
 *
 * Return: Nothing.
*/
void string_print(char *str)
{
	int index = 0;

	if (!str)
	{
		return;
	}
	while (str[index] != '\0')
	{
		character_print(str[index]);
		index++;
	}
}

/**
 * character_print - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
*/
int character_print(char c)
{
	static int buffer_index;
	static char write_buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(1, write_buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUFFER_FLUSH)
	{
		write_buffer[buffer_index++] = c;
	}
	return (1);
}
