#include "shell.h"
/**
 * free_shell_data - Frees the allocated memory for shell data.
 * @datash: A pointer to the data_shell structure.
 *
 * Return: No return value.
*/
void free_shell_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}
	free(datash->_environ);
	free(datash->pid);
}
/**
 * initialize_shell_data - Initializes the shell data structure.
 * @datash: A pointer to the data_shell structure.
 * @av: An array of command-line arguments.
 *
 * Return: No return value.
*/
void initialize_shell_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;
	for (i = 0; environ[i]; i++)
		;
	datash->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = strdup(environ[i]);
	}
	datash->_environ[i] = NULL;
	datash->pid = itoa(getpid());
}
/**
 * main - Entry point for the shell program.
 * @ac: The number of command-line arguments.
 * @av: An array of command-line arguments.
 *
 * Return: The exit status of the shell.
*/

int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;
	signal(SIGINT, handle_sigint);
	initialize_shell_data(&datash, av);
	shell_loop(&datash);
	free_shell_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
