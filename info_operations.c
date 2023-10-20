#include "shell.h"

/**
 * initialize_info - Initializes the info_t struct.
 * @info: The address of the struct to be initialized.
*/
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * populate_info - Populates the info_t struct with the argument vector.
 * @info: The address of the struct to be populated.
 * @argv: The argument vector.
*/
void populate_info(info_t *info, char **argv)
{
	int i = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * release_info - Frees the fields in the info_t struct.
 * @info: The address of the struct.
 * @freeAll: True if freeing all fields.
*/
void release_info(info_t *info, int freeAll)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (freeAll)
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
		character_print(BUF_FLUSH);
	}
}
