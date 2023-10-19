#include "shell.h"
/**
 * handleSIGINT - Handles the SIGINT signal (Ctrl+C) for the shell.
 * @signal: The signal number received (ignored).
*/
void handleSIGINT(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
