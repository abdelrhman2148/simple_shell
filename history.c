#include "shell.h"

/**
 * get_history_file - Retrieves the path to the shell's history file
 * @info: A pointer to the parameter struct
 *
 * This function is responsible for constructing and returning the path to
 * the shell's history file based on the user's home directory. It uses the
 * information provided in the 'info' struct to locate the home directory.
 *
 * @info: A struct containing necessary information.
 *
 * Return: A dynamically allocated string containing the full path
 * to the history file. It is the caller's responsibility
 *                            to free this memory when done.
*/
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * write_history - Creates a new history file or appends to an existing one.
 * @info: A pointer to the parameter struct, which contains relevant information.
 *
 * This function is responsible for writing the history of commands to a file.
 * It opens a file, specified by the 'filename' parameter, and writes each
 * command from the 'history' linked list to the file.
 *
 * @info: A pointer to the parameter struct.
 *
 * Return: Returns 1 on success, or -1 on failure.
*/
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads the command history from a file into memory.
 * @info: A pointer to the struct containing relevant information.
 *
 * This function opens and reads the command history from a file specified
 * in the 'info' struct. It loads the history into memory for later use.
 *
 * @info: A pointer to the struct that contains information about the history file.
 *
 * Return: The number of commands read (histcount) on success, 0 on failure.
*/
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds a new entry to the history linked list.
 *
 * This function is responsible for adding a new entry to a history linked list
 * which maintains a record of previously executed commands.
 *
 * @info: A structure containing potential arguments and information used in the operation.
 * @buf: The buffer containing the command or input to be added to the history.
 * @linecount: The current line count, often referred to as histcount.
 *
 * Return: Always returns 0 to indicate successful execution.
*/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 *
 * This function renumbers the history linked list, assigning a new sequential
 * number to each node in the list. This is useful when making changes to the
 * history, ensuring that the list remains in an orderly fashion.
 *
 * @info: A structure containing potential arguments. Used to maintain context.
 *
 * Return: The new histcount, which represents the total number of nodes in the
 * updated history list.
*/
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
