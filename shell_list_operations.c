#include "shell.h"
/**
 * add_separator_node_end - Appends a separator node
 *                           to the end of a separator list.
 * @head: A pointer to the head of the separator list.
 * @sep: The separator character (e.g., ; | &).
 *
 * Return: A pointer to the updated head of the separator list.
*/
sep_list *add_separator_node_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (*head);
}
/**
 * free_separator_list - Frees memory allocated for a separator list.
 * @head: A pointer to the head of the separator list.
*/
void free_separator_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
/**
 * add_line_node_end - Appends a line node to the end of a line list.
 * @head: A pointer to the head of the line list.
 * @line: A string representing a line of text.
 *
 * Return: A pointer to the updated head of the line list.
*/
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);
	new->line = line;
	new->next = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (*head);
}
/**
 * free_line_list - Frees memory allocated for a line list.
 * @head: A pointer to the head of the line list.
*/
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
