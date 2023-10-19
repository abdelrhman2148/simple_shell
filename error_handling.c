#include "shell.h"

/**
 * generateError - Generates an error message based on the evaluation code.
 * @datash: The data_shell structure.
 * @eval: The evaluation code.
 * Return: The error message.
*/
char *generateError(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
		case -1:
			error = generateEnvError(datash);
			break;
		case 126:
			error = generatePathError(datash);
			break;
		case 127:
			error = error_not_found(datash);
			break;
		case 2:
			if (_strcmp("exit", datash->args[0]) == 0)
				error = error_exit_shell(datash);
			else if (_strcmp("cd", datash->args[0]) == 0)
				error = error_get_cd(datash);
			break;
	}
	return (error);
}

/**
 * displayError - Displays an error message to the standard error.
 * @datash: The data_shell structure.
 * @error: The error message.
 * @eval: The evaluation code.
*/
void displayError(data_shell *datash, char *error, int eval)
{
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	datash->status = eval;
}
