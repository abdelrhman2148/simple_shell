#include "shell.h"

/**
 * analyzeEnvironment - Analyzes the environment variables and stores them.
 * @envVars: Pointer to the linked list for environment variables.
 * @input: The input string to analyze.
 * @data: Pointer to the data_shell structure.
*/
void analyzeEnvironment(r_var **envVars, char *input, data_shell *data)
{
	int row, chr, j, valueLength;
	char **environment = data->_environ;

	for (row = 0; environment[row]; row++)
	{
		for (j = 1, chr = 0; environment[row][chr]; chr++)
		{
			if (environment[row][chr] == '=')
			{
				valueLength = _strlen(environment[row] + chr + 1);
				add_rvar_node(envVars, j,
						environment[row] + chr + 1,
						valueLength);
				return;
			}
			if (input[j] == environment[row][chr])
				j++;
			else
				break;
		}
	}
	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t'
				|| input[j] == ';'
				|| input[j] == '\n')
			break;
	}
	add_rvar_node(envVars, j, NULL, 0);
}

/**
 * checkVariables - Checks for special variables in the input string.
 * @envVars: Pointer to the linked list for environment variables.
 * @input: The input string to check.
 * @statusString: The status string.
 * @data: Pointer to the data_shell structure.
 * Return: The number of characters processed.
*/
int checkVariables(r_var **envVars, char *input,
		char *statusString, data_shell *data)
{
	int i, last, pidLength;

	last = _strlen(statusString);
	pidLength = _strlen(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				add_rvar_node(envVars, 2, statusString, last),
					i++;
			else if (input[i + 1] == '$')
				add_rvar_node(envVars, 2, data->pid, pidLength),
					i++;
			else if (input[i + 1] == '\n' ||
					input[i + 1] == '\0' || input[i + 1] == ' ' ||
					input[i + 1] == '\t' || input[i + 1] == ';')
				add_rvar_node(envVars, 0, NULL, 0);
			else
				analyzeEnvironment(envVars, input + i, data);
		}
	}
	return (i);
}

/**
 * replaceVariables - Replaces variables in the input string with their values.
 * @envVars: Pointer to the linked list for environment variables.
 * @input: The input string to replace variables in.
 * @newInput: The string to store the result in.
 * @newInputLength: The length of the newInput buffer.
 * Return: The modified input string.
*/
char *replaceVariables(r_var **envVars,
		char *input, char *newInput, int newInputLength)
{
	r_var *index;
	int i, j, k;

	index = *envVars;
	for (j = i = 0; i < newInputLength; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				newInput[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					newInput[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			newInput[i] = input[j];
			j++;
		}
	}
	return (newInput);
}

/**
 * replaceInputVariables - Replaces variables in the input string.
 * @input: The input string.
 * @datash: Pointer to the data_shell structure.
 * Return: The modified input string.
*/
char *replaceInputVariables(char *input, data_shell *datash)
{
	r_var *environmentVariables = NULL;
	char *statusString, *newInput;
	int originalLength, newInputLength;

	statusString = aux_itoa(datash->status);
	originalLength = checkVariables(&environmentVariables,
			input, statusString, datash);

	if (environmentVariables == NULL)
	{
		free(statusString);
		return (input);
	}
	r_var *index = environmentVariables;

	newInputLength = 0;
	while (index != NULL)
	{
		newInputLength += (index->len_val - index->len_var);
		index = index->next;
	}
	newInputLength += originalLength;
	newInput = malloc(sizeof(char) * (newInputLength + 1));
	newInput[newInputLength] = '\0';
	newInput = replaceVariables(&environmentVariables,
			input, newInput, newInputLength);

	free(input);
	free(statusString);
	free_rvar_list(&environmentVariables);

	return (newInput);
}
