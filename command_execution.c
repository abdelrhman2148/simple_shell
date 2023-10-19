#include "shell.h"

/**
 * convertSeparators - Convert special characters for command separation.
 * @input: The input string.
 * @bool: Flag to indicate conversion direction 0 for forward, 1 for backward.
 *
 * Return: The modified input string.
*/
char *convertSeparators(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * addNodes - Add separator and line nodes to their respective lists.
 * @head_s: Pointer to the separator list head.
 * @head_l: Pointer to the line list head.
 * @input: The input string.
*/
void addNodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = convertSeparators(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			addSepNodeEnd(head_s, input[i]);
		if (input[i] == '|' || input[i] == '&')
		{
			addSepNodeEnd(head_s, input[i]);
			i++;
		}
	}
	line = _strtok(input, ";|&");

	do {
		line = convertSeparators(line, 1);
		addLineNodeEnd(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * advanceToNext - Advance to the next separator and line.
 * @list_s: Pointer to the separator list.
 * @list_l: Pointer to the line list.
 * @datash: Pointer to the data_shell struct.
*/
void advanceToNext(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loopSep;
	sep_list *ls_s;
	line_list *ls_l;

	loopSep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loopSep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loopSep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loopSep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loopSep)
			ls_s = ls_s->next;
	}
	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * executeCommands - Split and execute commands from input.
 * @datash: Pointer to the data_shell struct.
 * @input: The input string.
 * Return: 0 if the loop should exit, 1 otherwise.
*/
int executeCommands(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = splitLine(datash->input);
		loop = executeLine(datash);
		free(datash->args);

		if (loop == 0)
			break;
		advanceToNext(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}
	freeSepList(&head_s);
	freeLineList(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * splitLine - Split an input line into tokens.
 * @input: The input line.
 * Return: An array of tokens.
*/
char **splitLine(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;
	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}
	return (tokens);
}
