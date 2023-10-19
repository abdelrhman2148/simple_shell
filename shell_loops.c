#include "shell.h"
/**
 * remove_comments - this remove comments
 * @input: input
 * Return: input
*/
char *remove_comments(char *input)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}
			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}
	if (up_to != 0)
	{
		input = _realloc_memory(input, i, up_to + 1);
		input[up_to] = '\0';
	}
	return (input);
}
/**
 * shell_loop - shell for func
 * @datash: data
*/
void shell_loop(shell_data *datash)
{
	int loop, is_end_of_file;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_input(&is_end_of_file);
		if (is_end_of_file != -1)
		{
			input = remove_comments(input);
			if (input == NULL)
				continue;
			if (check_syntax_error(datash, input) == 1)
			{
				datash->exit_status = 2;
				free(input);
				continue;
			}
			input = replace_variable(input, datash);
			loop = separate_commands(datash, input);
			datash->command_counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
