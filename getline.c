#include "shell.h"
/**
 * input_buf - Read and buffer chained commands.
 *
 * @info: A pointer to the parameter struct.
 * @buf: A pointer to the address of the buffer.
 * @len: A pointer to the address of the length variable.
 *
 * Return: ssize_t - The number of bytes read.
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Reads a line of input from the shell exclud the newline char.
 *
 * @info: A structure containing information about the shell.
 *
 * This function is responsible for reading user input from shell excluding
 * the trailing newline character. It uses an input buffer and handles cases
 * such as reaching the end of file (EOF).
 * The input is stored in the 'arg' member of the 'info' structure.
 *
 * Return: The number of bytes read, or -1 in case of EOF.
*/
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads data from a file descriptor into a buffer.
 *
 * @info: A pointer to the information structure.
 * @buf: The buffer where data will be stored.
 * @i: A pointer to the size of the buffer.
 *
 * Return: ssize_t The number of bytes read, or an error code.
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Reads the next line of input from STDIN.
 * @info: A struct that contains relevant information.
 * @ptr: Address of a pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * This function is responsible for reading input from STDIN.
 * It can work with a preallocated buffer or allocate a new one as needed.
 * It also keeps track of the current position and length of the input buffer.
 *
 * Return: The number of bytes read.
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Signal handler for SIGINT (Ctrl-C)
 *
 * This function is responsible for handling the SIGINT signal
 * (Ctrl-C) in an interactive shell.
 *
 * @sig_num: The signal number (in this case, SIGINT)
 *
 * Return: This function does not return a value (void).
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
