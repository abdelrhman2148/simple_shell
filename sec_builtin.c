#include "shell.h"

/**
 * _myhistory - This function display the command history list presenting each
 *              command on a separate line with line numbers, starting at 0.
 * @info: A structure containing potential arguments
 * ensuring a consistent function prototype.
 * Return: Always returns 0 to indicate successful execution.
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias from the shell's alias list
 *
 * This function removes an alias identified by the provided string from the
 * list of aliases in the shell's information structure (info_t).
 *
 * @info: A pointer to the shell's information structure.
 * @str:  The string containing the alias to be removed.
 *
 * Return: 0 on success, 1 on error.
*/
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Sets an alias for a given string in the shell.
 *
 * @info: The struct that holds information about the shell.
 * @str: The string containing the alias to be set.
 * Should be in the format "alias_name=command".
 *
 * Return: Returns 0 on success, 1 on error.
*/
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints the content of an alias node in user-friendly format.
 * @node: Pointer to the alias node containing alias definition.
 *
 * This function extracts and prints an alias definition from the given node.
 * It formats the alias definition with single quotes
 * and outputs it to the standard output.
 * If the node is NULL, it indicates an error.
 *
 * Return: 0 on success (alias printed), 1 on error (node is NULL).
*/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Implements the alias command, similar to 'man alias'.
 * @info: A structure containing potential arguments and aliases.
 *
 * This function allows users to define and manage command aliases.
 * If called with no arguments, it lists all defined aliases. When provided
 * with alias definitions, it creates or updates aliases.
 *
 * Return: Always returns 0.
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
