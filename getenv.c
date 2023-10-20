#include "shell.h"

/**
 * get_environ - Copies the string array of environment variables (environ).
 *
 * This function creates a copy of the environment variables and returns
 * it as a string array. It's used to maintain a constant function prototype.
 *
 * @info: A structure containing potential argument not used in this function.
 * Return: Always returns 0 to indicate success.
*/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable from a list
 * @info: A structure that holds information about the environment.
 * @var: The name of the environment variable to be removed.
 *
 * This function removes an environment variable specified by 'var' from the
 * list of environment variables in the 'info' structure. It iterates through
 * the list and checks if each variable matches 'var', and if found, it removes
 * it.
 *
 * Return: 1 if the variable was successfully deleted, 0 otherwise.
*/
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initializes a new environment variable or modifies an exist one.
 *
 * @info: A structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * @var: The string representing the environment variable name.
 * @value: The string representing the value to be associated with the var.
 *
 * Return: Always returns 0 to indicate success.
*/
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
