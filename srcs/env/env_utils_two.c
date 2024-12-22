#include "minishell.h"

void	add_if_key_exists(char *key, char *value)
{
	t_env	*temp;

	temp = get_info()->env;
	while (temp)
	{
		if (!ft_strcmp(temp -> key, key))
		{
			temp -> value = value;
			return ;
		}
		temp = temp -> next;
	}
}
