#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: A pointer to the first node in the list.
 *
 * Return: The size of the linked list.
*/
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Convert a linked list of strings to an array of strings
 * @head: Pointer to the first node of the linked list
 *
 * Return: A dynamically allocated array of strings, or NULL.
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of a linked list of struct of type list_t.
 * @h: A pointer to the first node of the linked list.
 *
 * Return: The size of the linked list (the number of nodes).
*/
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * node_starts_with - Find a node in a linked list whose string
 *            starts with a given prefix and next character.
 * @node: A pointer to the head of the linked list.
 * @prefix: The string to match at the beginning of each node's string.
 * @c: The next character after the prefix that should match.
 *
 * This function iterates through the linked list and checks if
 *   the string in each node starts with the specified 'prefix'
 *   and if the character immediately following the prefix matches 'c'.
 * If a match is found, it returns the matching node otherwise it returns NULL
 *
 * Return: A pointer to the matched node or NULL if no match is found.
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a node in a linked list
 * @head: Pointer to the head of the linked list
 * @node: Pointer to the node whose index is to be found
 *
 * This function traverses a linked list, starting from the head
 * and searches for a specific node.
 * If the node is found, its index in the list is returned.
 * If the node is not found, -1 is returned.
 *
 * @head: Pointer to the head of the linked list.
 * @node: Pointer to the node for which the index is needed.
 *
 * Return: The index of the node if found, or -1 if node is not in the list.
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
