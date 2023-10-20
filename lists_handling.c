#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of a linked list.
 *
 * @head: Pointer to the address of the head node.
 * @str: The string to be stored in the new node.
 * @num: The node index used by the history.
 *
 * This function creates a new node, initializes its fields, and adds it to the
 * start of the linked list. If successful, it returns the size of the list.
 *
 * Return: The size of the updated list.
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a new node to the end of a linked list.
 * @head: A pointer to the address of the head node.
 * @str: The string to be stored in the new node.
 * @num: The index used by the history.
 *
 * This function creates a new node with the given string and index
 * and appends it to the end of the linked list pointed to by 'head'.
 *
 * Return: The size of the updated list.
*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Print the string element of a list_t linked list.
 * @h: Pointer to the first node of the linked list.
 *
 * This function traverses the linked list and prints the string element
 * of each node. If the string is NULL, it prints "(nil)".
 *
 * @return: The size of the linked list.
*/
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - Deletes a node from a linked list at the specified index.
 * @head: A pointer to the address of the first node in the list.
 * @index: The index of the node to be deleted.
 *
 * This function removes a node at the given index in a linked list.
 * It also frees the memory associated with the deleted node
 * including its string data.
 *
 * Return: 1 on success, 0 on failure.
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a linked list
 *
 * This function iterates through a linked list, deallocating memory.
 *
 * @head_ptr: Pointer to the head node of the list
 *
 * This function takes a pointer to the head node of a linked list and
 * frees each node and the memory allocated for its string data.
 * After the list is freed, the head pointer is set to NULL.
*/
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
