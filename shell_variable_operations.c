#include "shell.h"

/**
 * add_replace_var_node - Adds a replace variable node to the list.
 * @head: Pointer to the head of the list.
 * @length_var: Length of the variable.
 * @value: Value of the variable.
 * @length_value: Length of the value.
 * Return: A pointer to the updated head of the list.
*/
r_var *add_replace_var_node(r_var **head, int length_var,
		char *value, int length_value)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);
	new->len_var = length_var;
	new->val = value;
	new->len_val = length_value;

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
 * free_replace_var_list - Frees the memory allocated.
 * @head: Pointer to the head of the list.
*/
void free_replace_var_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
