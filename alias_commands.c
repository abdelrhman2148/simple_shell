#include "shell.h"

/**
 * display_history - Display the command history with line numbers.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
*/
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias_command - Unset an alias.
 * @info: Parameter struct.
 * @alias_str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error
*/
int unset_alias_command(info_t *info, char *alias_str)
{
	char *equals_pos, original_char;
	int result;

	equals_pos = _strchr(alias_str, '=');
	if (!equals_pos)
		return (1);
	original_char = *equals_pos;
	*equals_pos = '\0';
	result = delete_node_at_index(&(info->alias), get_node_index(info->alias,
				node_starts_with(info->alias, alias_str, -1)));
	*equals_pos = original_char;
	return (result);
}

/**
 * set_alias_command - Set an alias.
 * @info: Parameter struct.
 * @alias_str: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error
*/
int set_alias_command(info_t *info, char *alias_str)
{
	char *equals_pos;

	equals_pos = _strchr(alias_str, '=');
	if (!equals_pos)
		return (1);
	if (!*++equals_pos)
		return (unset_alias_command(info, alias_str));
	unset_alias_command(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_single_alias - Print a single alias string.
 * @alias_node: The alias node.
 *
 * Return: Always 0 on success, 1 on error
*/
int print_single_alias(list_t *alias_node)
{
	char *equals_pos = NULL, *alias = NULL;

	if (alias_node)
	{
		equals_pos = _strchr(alias_node->str, '=');
		for (alias = alias_node->str; alias <= equals_pos; alias++)
		{
			_putchar(*alias);
			_putchar('\'');
			_puts(equals_pos + 1);
			_puts("'\n");
			return (0);
		}
	}
	return (1);
}

/**
 * alias_command - Mimics the alias built-in.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
*/
int alias_command(info_t *info)
{
	int i = 0;
	char *equals_pos = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_single_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equals_pos = _strchr(info->argv[i], '=');
		if (equals_pos)
			set_alias_command(info, info->argv[i]);
		else
			print_single_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
