#include "shell.h"
/**
 * clear_info - Initializes an info_t struct with default values.
 *
 * @info: A pointer to the info_t struct to be initialized.
 *
 * This function takes a pointer to an info_t struc
 * and sets its members to default values, making it ready for use.
 * The members include 'arg,' 'argv,' 'path,' and 'argc,'
 * which are all initialized to NULL or 0 as appropriate.
*/
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info - Initializes the 'info_t' struct with information.
 *
 * @info: A pointer to the 'info_t' struct to be initialized.
 * @av: The argument vector (array of strings).
*/
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees the fields of an info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: If true, frees all fields, including optional ones.
 *
 * This function is responsible for freeing the memory associated
 * with various fields within the info_t struct.
 * The 'info' parameter is a pointer to the struct
 * that holds information related to a shell.
 * If 'all' is true, it frees all fields, including optional
 * ones like command history and aliases.
*/
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
