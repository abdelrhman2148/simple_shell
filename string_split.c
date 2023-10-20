/**
 * split_string - Splits an input string into words using specified delimiters.
 * @input_string: The string to split.
 * @delimiter_string: The delimiter string to use for splitting.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string(char *input_string, char *delimiter_string)
{
	int i, j, k, m, num_words = 0;
	char **word_array;

	if (input_string == NULL || input_string[0] == '\0')
		return (NULL);
	if (!delimiter_string)
		delimiter_string = " ";
	for (i = 0; input_string[i] != '\0'; i++)
	{
		if (!is_delimiter(input_string[i], delimiter_string)
				&& (is_delimiter(input_string[i + 1],
						delimiter_string)
					|| !input_string[i + 1]))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	word_array = malloc((1 + num_words) * sizeof(char *));
	if (!word_array)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(input_string[i], delimiter_string))
			i++;
		k = 0;
		while (!is_delimiter(input_string[i + k], delimiter_string)
				&& input_string[i + k])
			k++;
		word_array[j] = malloc((k + 1) * sizeof(char));
		if (!word_array[j])
			for (k = 0; k < j; k++)
				free(word_array[k]);
		free(word_array);
		return (NULL);
		for (m = 0; m < k; m++)
			word_array[j][m] = input_string[i++];
		word_array[j][m] = '\0';
		word_array[j] = NULL;
		return (word_array);
	}
}

/**
 * split_string_v2 - Splits an input string into words using
 *              a single character delimiter.
 * @input_string: The string to split.
 * @delimiter: The delimiter character to use for splitting.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
*/
char **split_string_v2(char *input_string, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **word_array;

	if (input_string == NULL || input_string[0] == '\0')
		return (NULL);
	for (i = 0; input_string[i] != '\0'; i++)
		if ((input_string[i] != delimiter && input_string[i + 1] == delimiter)
				|| (input_string[i] != delimiter && !input_string[i + 1])
				|| input_string[i + 1] == delimiter)
			num_words++;
	if (num_words == 0)
		return (NULL);
	word_array = malloc((1 + num_words) * sizeof(char *));
	if (!word_array)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input_string[i] == delimiter && input_string[i] != delimiter)
			i++;
		k = 0;
		while (input_string[i + k] != delimiter && input_string[i + k]
				&& input_string[i + k] != delimiter)
			k++;
		word_array[j] = malloc((k + 1) * sizeof(char));
		if (!word_array[j])
		{
			for (k = 0; k < j; k++)
				free(word_array[k]);
			free(word_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			word_array[j][m] = input_string[i++];
		word_array[j][m] = '\0';
	}
	word_array[j] = NULL;
	return (word_array);
}