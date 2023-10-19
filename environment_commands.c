#include "shell.h"

/**
 * copyEnvironmentVariable - Copies an environment variable.
 * @name: The name part of the environment variable.
 * @value: The value part of the environment variable.
 * Return: A new string in the "name=value" format.
*/
char *copyEnvironmentVariable(const char *name, const char *value)
{
	int len_name = _strlen(name);
	int len_value = _strlen(value);
	char *new = malloc(sizeof(char) * (len_name + len_value + 2));

	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * setEnvironmentVariable - Sets or updates an environment variable.
 * @name: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * @datash: The data_shell structure.
*/
void setEnvironmentVariable(const char *name,
		const char *value, data_shell *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copyEnvironmentVariable(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}
	datash->_environ = _reallocDoublePointer(datash->_environ,
			i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copyEnvironmentVariable(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * setenvCommand - Implements the setenv command.
 * @datash: The data_shell structure.
 * Return: 1 if successful, 0 otherwise.
*/
int setenvCommand(data_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	setEnvironmentVariable(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * unsetenvCommand - Implements the unsetenv command.
 * @datash: The data_shell structure.
 * Return: 1 if successful, 0 otherwise.
*/
int unsetenvCommand(data_shell *datash)
{
	int i, k = -1;
	char *var_env;
	char *name_env;
	char **realloc_environ;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (k));
	for (i = 0, j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[k] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
