#include "shell.h"

/**
 * handleSIGINT - 
 * @signal: 
*/
void handleSIGINT(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
