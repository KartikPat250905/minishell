/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:21:19 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/21 20:21:21 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	add_to_env_list(char *key, char *value, int is_env)
{
	t_env	*new;
	t_env	*temp;
	t_env	*head;

	if (!is_key_in_env(key))
	{
		temp = get_info()->env;
		while (temp)
		{
			if (!ft_strcmp(temp -> key, key))
			{
				temp -> value = value;
				return (0);
			}
			temp = temp -> next;
		}
		return (0);
	}
	new = gc_alloc(sizeof(t_env));
	if (!new)
		return (1);
	new -> key = key;
	new -> value = value;
	new -> is_env = is_env;
	new -> next = NULL;
	head = get_info()->env;
	envadd(&head, new);
	return (0);
}

int	is_valid_number(const char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	handle_shvl(char **key, char **value)
{
	int	shell_lvl;

	if (!ft_strcmp(*key, "SHLVL"))
	{
		if (is_valid_number(*value))
		{
			printf("I am here\n");
			shell_lvl = ft_atoi(*value) + 1;
			if (shell_lvl > 999)
				shell_lvl = 1;
			printf("The shell lvl is %d\n", shell_lvl);
			free(*value);
			*value = ft_itoa(shell_lvl);
		}
		else
		{
			free(*value);
			*value = ft_strdup("1");
		}
	}
}

t_env	*init_env_node(char *env, int if_env)
{
	t_env	*node;
	char	*key;
	char	*value;

	node = gc_alloc(sizeof(t_env));
	if (!node)
		return (NULL);
	key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	value = ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env) - (ft_strchr(env, '=') - env) - 1);
	//handle_shvl(&key, &value);
	if (!key || !value)
	{
		free(key);
		free(value);
		free(env);
		return (NULL);
	}
	node -> key = key;
	node -> value = value;
	node -> is_env = if_env;
	node -> next = NULL;
	return (node);
}

void	envadd(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

// maybe make it void just use get_info()->envp = envp;
//creates linked list
void	fetch_envp(char **envp)
{
	int		i;
	t_env	*result;
	t_env	*temp;

	i = 0;
	result = NULL;
	if (!envp)
		return ;//(result);
	while (envp[i])
	{
		temp = init_env_node(envp[i], 1);
		if (!temp)
			return ;//(NULL);
		envadd(&result, temp);
		i++;
	}
	get_info()->env = result;
	//result->envp = build_envp(result);
	//char **built_envp(t_env *head);
	//return (result);
}
