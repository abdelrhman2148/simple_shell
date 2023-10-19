#include "shell.h"

/**
 * execute_line - 
 * @datash: 
 * Return: 
*/
int execute_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);
	builtin = get_builtin(datash->args[0]);
	if (builtin != NULL)
		return (builtin(datash));
	return (execute_command(datash));
}
