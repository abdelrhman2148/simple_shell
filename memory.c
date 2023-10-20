#include "shell.h"

/**
 * bfree - Frees a dynamically allocated memory pointer and sets it to NULL.
 *
 * This function takes a pointer to a dynamically allocated memory address and
 * frees the memory to prevent memory leaks. It also sets the pointer to NULL
 * to avoid potential access to invalid memory.
 *
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if memory is freed successfully, otherwise 0.
*/
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
