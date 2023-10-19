#include "shell.h"
/**
 * help_environment - 
 * Return: 
*/
void help_environment(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, _string_length(help));
}

/**
 * help_set_environment -
 * Return: 
 */
void help_set_environment(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _string_length(help));
}

/**
 * help_unset_environment -
 * Return: 
 */
void help_unset_environment(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _string_length(help));
}

/**
 * help_general_info - 
 * Return: 
 */
void help_general_info(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "These commands are defined internally. Type 'help' to see the list";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _string_length(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _string_length(help));
}

/**
 * help_exit_command - 
 * Return: 
 */
void help_exit_command(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "Exits the shell with a status of N. If N is omitted, the exit";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, _string_length(help));
}
