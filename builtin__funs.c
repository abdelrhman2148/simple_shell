#include "shell.h"

/**
 * exit_shell - Exit the shell.
 * @info: Structure containing potential arguments.
 *  Return: Exits the shell with a given exit status.
 *         (0) if info->argv[0] != "exit"
*/
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = str_to_int(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_errputs(info->argv[1]);
			_errputchar('\n');
			return (1);
		}
		info->err_num = str_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Change the current directory of the process.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
*/
int change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		string_print("cwd failure message here<<\n");
	if (!info->argv[1])
	{
		dir = get_environment_variable(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_environment_variable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_compare(info->argv[1], "-") == 0)
	{
		if (!get_environment_variable(info, "OLDPWD="))
		{
			string_print(s);
			character_print('\n');
			return (1);
		}
		string_print(get_environment_variable(info, "OLDPWD=")),
			character_print('\n');
		chdir_ret = chdir((dir = get_environment_variable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		print_error_message(info->argv[1]), write_stderr('\n');
	}
	else
	{
		set_environment_variable(info, "OLDPWD",
				get_environment_variable(info, "PWD="));
		set_environment_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_shell - Display help message (not yet implemented).
 * @info: Structure containing potential arguments.
 *  Return: Always 0
*/
int help_shell(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	string_print("Help call works. Function not yet implemented.\n");
	if (0)
		string_print(*arg_array);
	return (0);
}
