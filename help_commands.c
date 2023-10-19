#include "shell.h"

/**
 * displayHelp - Displays help information for built-in commands.
 * @datash: The data_shell structure.
 * Return: Always returns 1.
*/
int displayHelp(data_shell *datash)
{
	if (datash->args[1] == 0)
		printGeneralHelp();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		printSetenvHelp();
	else if (_strcmp(datash->args[1], "env") == 0)
		printEnvHelp();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		printUnsetenvHelp();
	else if (_strcmp(datash->args[1], "help") == 0)
		printHelpHelp();
	else if (_strcmp(datash->args[1], "exit") == 0)
		printExitHelp();
	else if (_strcmp(datash->args[1], "cd") == 0)
		printCdHelp();
	else if (_strcmp(datash->args[1], "alias") == 0)
		printAliasHelp();
	else
		write(STDERR_FILENO, datash->args[0], _strlen(datash->args[0]));
	datash->status = 0;
	return (1);
}
