#include "shell.h"

/**
 * changeDirectory - Change the current working directory based on the given path.
 * @datash: The data_shell structure.
 * @path: The path to change to.
*/
void changeDirectory(data_shell *datash, const char *path)
{
	char *error;
	char *currentDir;

	if (chdir(path) == -1)
	{
		error = error_get_cd(datash);
		if (error)
		{
			write(STDERR_FILENO, error, _strlen(error));
			free(error);
		}
	}
	else
	{
		setenv("OLDPWD", datash->_environ[findEnvIndex(datash, "PWD")], 1);
		currentDir = getcwd(NULL, 0);
		if (currentDir)
		{
			setenv("PWD", currentDir, 1);
			free(currentDir);
		}
	}
}

/**
 * cdShell - Change the current working directory based on the arguments.
 * @datash: The data_shell structure.
 * Return: 1 if successful, 0 otherwise.
*/
int cdShell(data_shell *datash)
{
	const char *dir = datash->args[1];

	if (dir == NULL)
	{
		cdToHome(datash);
	}
	else if (_strcmp("$HOME", dir) == 0 || _strcmp("~", dir) == 0 || _strcmp("--", dir) == 0)
	{
		cdToHome(datash);
	}
	else if (_strcmp("-", dir) == 0)
	{
		cdPrevious(datash);
	}
	else if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cdDot(datash);
	}
	else
	{
		changeDirectory(datash, dir);
	}
	return (1);
}
