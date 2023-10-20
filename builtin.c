#include "shell.h"

/**
 * _myexit - Exits the shell with a specified exit status.
 * @info: A structure containing potential arguments and
 *                                 information about the shell.
 *
 * This function is responsible for exiting
 *       the shell when the "exit" command is issued.
 * If an exit status is provided as an argument
 *                 it will be used as the exit status.
 *
 * @info: The structure containing shell information.
 *
 * Return: Returns the exit status
 * which is (0) if info->argv[0] is not "exit".
*/
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current working directory of the process
 * @info: A structure containing potential arguments and information needed
 *        to maintain a consistent function prototype.
 *
 * This function is responsible for changing the current working directory of
 * the process. It first checks if the shell is in interactive mode, and if it
 * is, it returns true. Then, it attempts to retrieve the current working
 * directory using the `getcwd` function. If successful, it proceeds to change
 * the directory as specified in the provided arguments.
 *
 * Return: Always returns 0.
*/
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _myhelp - Changes the current directory of the process.
 * @info: A structure containing potential arguments. It is used to maintain
 *        a constant function prototype.
 *
 * This function is responsible for handling the 'help' command. It takes
 * a structure 'info' as an argument, which typically includes command-line
 * arguments and other information. The function's primary purpose is to
 * provide help or instructions to the user about how to use the shell or
 * specific commands.
 * Return: Always returns 0 to indicate successful execution.
*/
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
