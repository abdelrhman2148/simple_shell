#include "shell.h"
/**
 * memory_copy - Copy memory from one location to another.
 * @new_pointer: The destination pointer where the memory will be copied to.
 * @pointer: The source pointer from which memory will be copied.
 * @size: The number of bytes to copy.
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
 * realloc_memory - Reallocate memory, optionally copying the existing content.
 * @pointer: The pointer to the memory block to reallocate.
 * @old_size: The current size of the memory block.
 * @new_size: The desired new size for the memory block.
 *
 * Return: A pointer to the reallocated memory block or NULL on failure.
*/
void *realloc_memory(void *pointer, unsigned int old_size,
		unsigned int new_size)
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
		return (pointer);
	new_pointer = malloc(new_size);
	if (new_pointer == NULL)
		return (NULL);
	if (new_size < old_size)
		memory_copy(new_pointer, pointer, new_size);
	else
		memory_copy(new_pointer, pointer, old_size);
	free(pointer);
	return (new_pointer);
}

/**
 * realloc_double_pointer - Reallocate a double pointer (array of strings).
 * @pointer: The pointer to the array of strings to reallocate.
 * @old_size: The current size of the array.
 * @new_size: The desired new size for the array.
 *
 * Return: A pointer to the reallocated array of strings or NULL on failure.
*/
char **realloc_double_pointer(char **pointer, unsigned int old_size,
		unsigned int new_size)
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
