#include "shell.h"
/**
 * _myenv - Prints the current environment variables.
 *
 * This function prints the list of environment variables to the standard output.
 *
 * @info: A structure containing potential arguments. Used to maintain a constant function prototype.
 *
 * Return: Always 0 to indicate successful execution.
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable
 * @info: Structure containing information about the environment
 * @name: The name of the environment variable to retrieve
 *
 * This function searches for the environment variable specified by 'name' in
 * the linked list of environment variables stored in 'info->env'. If it finds
 * a match, it returns the value of the environment variable. If no match is
 * found, it returns NULL.
 *
 * Returns: The value of the environment variable or NULL if not found.
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 *
 * This function is responsible for setting or modifying environment variables in a shell.
 * It takes a structure containing potential arguments to maintain a consistent function prototype.
 *
 * @param info: A pointer to a structure containing arguments and information.
 * @return: 0 on success, 1 on failure.
*/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove one or more environment variables
 * @info: A structure that contains information about the function arguments.
 *
 * This function is used to remove one or more environment variables. It takes
 * the arguments provided in 'info' and processes them for removal.
 *
 * @info: A structure that contains the following fields:
 *   - argc: The number of arguments in 'argv'.
 *   - argv: An array of argument strings.
 *
 * Return: Always returns 0, indicating successful execution.
*/
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates an environment linked list.
 *
 * This function populates a linked list with environment variables, providing
 * a convenient way to access and manipulate the environment variables in the
 * program.
 *
 * @info: A pointer to a structure containing potential arguments. It is used
 *        to maintain a constant function prototype.
 *
 * Return: Always returns 0 to indicate successful execution.
*/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
