#include "shell.h"
/**
 * execute_line - Execute a command or built-in function.
 * @datash: A pointer to the data_shell structure
 *                            containing command information.
 * Return: 1 if the first argument is NULL
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
