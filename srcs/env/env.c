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

#include "minishell.h"

int	add_to_env_list(char *key, char *value, int is_env)
{
	t_env	*new;
	t_env	*head;

	if (!key || !value)
		free_and_exit();
	if (!is_key_in_env(key))
	{
		add_if_key_exists(key, value);
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		free_and_exit();
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

t_env	*init_env_node(char *env, int if_env)
{
	t_env	*node;
	char	*key;
	char	*value;

	node = malloc(sizeof(t_env));
	if (!node)
		free_and_exit();
	key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	value = ft_substr(env, ft_strchr(env, '=') - env + 1,
			ft_strlen(env) - (ft_strchr(env, '=') - env) - 1);
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
		get_info()->env = new;
		return ;
	}
	current = (*lst);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

//creates linked list
void	fetch_envp(char **envp)
{
	int		i;
	t_env	*result;
	t_env	*temp;

	i = 0;
	result = NULL;
	if (!envp)
		return ;
	while (envp[i])
	{
		temp = init_env_node(envp[i], 1);
		if (!temp)
			return ;
		envadd(&result, temp);
		i++;
	}
	get_info()->env = result;
}
