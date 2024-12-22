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
