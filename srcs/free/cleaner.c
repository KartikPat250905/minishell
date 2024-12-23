#include "minishell.h"

void	free_env_list(void)
{
	t_env	*current;
	t_env	*next;

	current = get_info()->env;
	while (current != NULL)
	{
		next = current->next;
		if (current -> key)
			free(current->key);
		if (current -> value)
			free(current->value);
		free(current);
		current = next;
	}
	get_info()->env = NULL;
}

void	free_token_stack(t_token_stack *stack)
{
	t_token_node	*current;
	t_token_node	*next;

	if (stack == NULL)
		return ;
	current = stack -> top;
	while (current != NULL)
	{
		next = current->next;
		if (current -> value)
			free(current->value);
		free(current);
		current = next;
	}
	stack->top = NULL;
}

void	free_t_list(t_list **node)
{
	t_list	*next;
	t_list	*head;

	head = *node;
	//printf("I am in free_t_list\n");
	while (head != NULL)
	{
		next = head->next;
		if (head -> content)
			free(head -> content);
		free(head);
		head = next;
	}
	*node = NULL;
}
