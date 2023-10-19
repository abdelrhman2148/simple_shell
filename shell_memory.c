#include "shell.h"

/**
 * memory_copy - 
 * @new_pointer: 
 * @pointer: 
 * @size: 
 */
void memory_copy(void *new_pointer, const void *pointer, unsigned int size)
{
	char *char_pointer = (char *)pointer;
	char *char_new_pointer = (char *)new_pointer;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_new_pointer[i] = char_pointer[i];
}

/**
 * realloc_memory - 
 * @pointer: 
 * @old_size: 
 * @new_size: 
 *
 * Return: 
*/
void *realloc_memory(void *pointer, unsigned int old_size, unsigned int new_size)
{
	void *new_pointer;

	if (pointer == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(pointer);
		return (NULL);
	}
	if (new_size == old_size)
		return pointer;
	new_pointer = malloc(new_size);
	if (new_pointer == NULL)
		return (NULL);
	if (new_size < old_size)
		memory_copy(new_pointer, pointer, new_size);
	else
		memory_copy(new_pointer, pointer, old_size);
	free(pointer);
	return new_pointer;
}

/**
 * realloc_double_pointer - 
 * @pointer:
 * @old_size: 
 * @new_size: 
 *
 * Return: 
*/
char **realloc_double_pointer(char **pointer, unsigned int old_size, unsigned int new_size)
{
	char **new_pointer;
	unsigned int i;

	if (pointer == NULL)
		return (malloc(sizeof(char *) * new_size));
	if (new_size == old_size)
		return (pointer);
	new_pointer = malloc(sizeof(char *) * new_size);
	if (new_pointer == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		new_pointer[i] = pointer[i];
	free(pointer);
	return (new_pointer);
}
