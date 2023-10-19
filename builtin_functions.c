#include "shell.h"

/**
 * getBuiltinFunction - Get a pointer to the built-in function.
 * @command: The command name.
 * Return: A pointer to the built-in function, or NULL if not found.
*/
int (*getBuiltinFunction(char *command))(data_shell *)
{
	int i;
	builtin_t builtinFunctions[] = {
		{ "env", executeEnv },
		{ "exit", executeExit },
		{ "setenv", executeSetenv },
		{ "unsetenv", executeUnsetenv },
		{ "cd", executeCd },
		{ "help", executeHelp },
		{ NULL, NULL }
	};

	for (i = 0; builtinFunctions[i].name; i++)
	{
		if (_strcmp(builtinFunctions[i].name, command) == 0)
			return (builtinFunctions[i].function);
	}
	return (NULL);
}
