#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * 
 * This function checks if a file specified by its path is executable command.
 * An executable command is a regular file that can be executed as a program.
 * 
 * @info: The info struct, although not used in this function.
 * @path: The path to the file being checked.
 * 
 * Return:
 * - 1 if the file is an executable command.
 * - 0 if the file is not an executable command or
 *   if an error occurs during the check.
*/
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - Duplicate characters from a string within a specified range.
 *
 * This function takes a string and duplicates the characters in a specified
 * range defined by the 'start' and 'stop' indices. It copies the characters
 * from 'start' (inclusive) to 'stop' (exclusive) into a new buffer.
 *
 * @param pathstr: The original string to duplicate characters from.
 * @param start:   The starting index of the range (inclusive).
 * @param stop:    The stopping index of the range (exclusive).
 *
 * @return: A pointer to a new buffer containing the duplicated characters.
*/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH environment var.
 *
 * This function searches for a command in the specified PATH string
 * and returns its full path if found.
 *
 * @param info - The info struct containing additional information.
 * @param pathstr - The PATH environment variable string.
 * @param cmd - The command to find.
 *
 * @return - The full path of the command if found, or NULL if not found.
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
