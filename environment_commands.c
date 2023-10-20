#include "shell.h"

/**
 * display_environment - Display the current environment variables.
 * @info: Structure containing potential arguments.
 * Return: Always 0
*/
int display_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_environment_variable - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: The environment variable name.
 *
 * Return: The value of the environment variable, or NULL if not found.
*/
char *get_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = string_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initialize a new environment
 *                         variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		print_error_message("Incorrect number of arguments\n");
		return (1);
	}
	if (set_environment_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0
*/
int unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		print_error_message("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		remove_environment_variable(info, info->argv[i]);
	return (0);
}

/**
 * populate_environment_list - Populate the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0
*/
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
