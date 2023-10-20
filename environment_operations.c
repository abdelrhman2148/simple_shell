#include "shell.h"

/**
 * retrieve_environment - Retrieve a copy of the environment as a string array.
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 *
 * Return: A string array representing the environment.
*/
char **retrieve_environment(info_t *info)
{
	if (!info->environ || info->environment_changed)
	{
		info->environ = list_to_string_array(info->env);
		info->environment_changed = 0;
	}
	return (info->environ);
}

/**
 * remove_environment_variable - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * @variable: The environment variable to be removed.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
*/
int remove_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->environment_changed);
}

/**
 * set_environment_variable - Initialize a new environment variable
 *         or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * @variable: The name of the environment variable.
 * @value: The value of the environment variable.
 *
 * Return: Always 0.
*/
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);
	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->environment_changed = 1;
	return (0);
}
