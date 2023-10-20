#include "shell.h"

/**
 * _memset - Fills a block of memory with a specified byte value
 *
 * This function sets the first 'n' bytes of the memory area pointed to by 's'
 * to the specified byte 'b'.
 *
 * @s: A pointer to the memory area to be filled.
 * @b: The byte value used to fill the memory area.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area 's'.
*/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees a dynamically allocated array of strings and the array itself.
 * @pp: A pointer to the array of strings to be freed.
 *
 * This function takes a pointer to an array of strings and
 * frees each individual string within the array using the free() function.
 * It then frees the array itself.
 * It's essential to use this function to avoid memory leaks
 * when working with dynamically allocated string arrays.
*/
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * _realloc - Reallocate a block of memory with optional resizing.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Size in bytes of the old memory block.
 * @new_size: Size in bytes of the new memory block.
 *
 * This function reallocates a block of memory pointed to by 'ptr'.
 * If 'ptr' is NULL, it behaves like 'malloc' by allocating
 * a new block of 'new_size' bytes. If 'new_size' is 0
 * it behaves like 'free' by freeing the memory block pointed to by 'ptr'.
 * If 'new_size' is equal to 'old_size', no changes are made
 * and the original 'ptr' is returned.
 *
 * Return: A pointer to the reallocated memory block, or NULL.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
