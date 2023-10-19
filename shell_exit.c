#include "shell.h"
/**
 * handle_exit - Handles the exit command.
 *
 * @datash: Pointer to the data_shell structure.
 *
 * Return: 0 on successful exit, 1 on error.
 */
int handle_exit(data_shell *datash)
{
	unsigned int exit_status;
	int is_valid_digit;
	int str_length;
	int is_too_big;

	if (datash->args[1] != NULL)
	{
		exit_status = _atoi(datash->args[1]);
		is_valid_digit = _isdigit(datash->args[1]);
		str_length = _strlen(datash->args[1]);
		is_too_big = exit_status > (unsigned int)INT_MAX;

		if (!is_valid_digit || str_length > 10 || is_too_big)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (exit_status % 256);
	}
	return (0);
}
