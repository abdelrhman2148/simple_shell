/**
 * str_length - Returns the length of a string.
 * @str: The string to calculate the length of.
 *
 * Return: The integer length of the string.
*/
int str_length(char *str)
{
	int length = 0;

	if (!str)
		return (0);
	while (*str++)
	{
		length++;
	}
	return (length);
}

/**
 * str_compare - Performs a lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: A negative value if str1 < str2,
 *           a positive value if str1 > str2, and 0 if str1 == str2.
*/
int str_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
	{
		return (*str1 < *str2 ? -1 : 1);
	}
}

/**
 * string_starts_with - Checks if the haystack starts with the needle.
 * @haystack: The string to search.
 * @needle: The substring to find at the beginning of the haystack.
 *
 * Return: The address of the next character, or NULL if not found.
*/
char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 * string_concatenate - Concatenates two strings.
 * @destination: The destination buffer where the result is stored.
 * @source: The source buffer to be appended.
 *
 * Return: A pointer to the destination buffer.
*/
char *string_concatenate(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
	{
		destination++;
	}
	while (*source)
	{
		*destination++ = *source++;
	}
	*destination = *source;
	return (result);
}
