#include "shell.h"

/**
 * compareEnvName - Compares the name part of an environment variable.
 * @nenv: The environment variable.
 * @name: The name to compare.
 * Return: The position of the first character after the equal sign.
*/
int compareEnvName(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}
	return (i + 1);
}

/**
 * getEnvironmentVariable - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 * @_environ: The environment array.
 * Return: The value of the environment variable or NULL if not found.
*/
char *getEnvironmentVariable(const char *name, char **_environ)
{
	char *ptr_env;
	int i, move;

	ptr_env = NULL;
	move = 0;

	for (i = 0; _environ[i]; i++)
	{
		move = compareEnvName(_environ[i], name);
		if (move)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + move);
}

/**
 * displayEnvironment - Displays the environment variables.
 * @datash: The data_shell structure.
 * Return: 1.
*/
int displayEnvironment(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		for (j = 0; datash->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
