#include "shell.h"
/**
 * help_command - Displays help information for the 'help' command.
 *
 * Return: This function does not return a value.
*/
void help_command(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _string_length(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _string_length(help));
}
/**
 * help_alias_command - Displays help information for the 'alias' command.
 *
 * Return: This function does not return a value.
*/
void help_alias_command(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _string_length(help));
}
/**
 * help_cd_command - Displays help information for the 'cd' command.
 *
 * Return: This function does not return a value.
*/
void help_cd_command(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _string_length(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _string_length(help));
}
