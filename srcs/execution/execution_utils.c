/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:21:14 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 19:21:16 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

bool	unclosed_quotes(char *str)
{
	int		i;
	int		dq;
	int		sq;
	bool	unclosed;

	i = 0;
	dq = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			dq++;
		else if (str[i] == '\'')
			sq++;
		i++;
	}
	unclosed = (dq % 2);
	if (!unclosed)
		unclosed = (sq % 2);
	return (unclosed);
}

// env var format: \$[A-Za-z_][A-Za-z0-9_]*
char	*env_expander(char *str)
{
	char	*pre;
	char	*env_var;
	char	*value;
	char	*tmp;
	int		in_sq;
	int		in_dq;
	int		i;
	int		start;
	char	single_char[2];

	pre = gc_strdup("");
	in_sq = 0;
	in_dq = 0;
	i = 0;
	single_char[1] = '\0';
	while (str[i])
	{
		if (str[i] == '"' && !in_sq)
		{
			in_dq = !in_dq;
			i++;
			continue ;
		}
		else if (str[i] == '\'' && !in_dq)
		{
			in_sq = !in_sq;
			i++;
			continue ;
		}
		// check for a variable expansion
		if (str[i] == '$' && !in_sq)
		{
			if (str[i + 1] == '?')
			{
				// handle last exit code, hardcoded for now to 42
				char *exit_code_str = ft_itoa(g_exit_status);
				tmp = gc_strjoin(pre, exit_code_str);
				gc_free(pre);
				gc_free(exit_code_str);
				pre = tmp;
				i += 2; // past "$?"
				continue ;
			}
			else if ((str[i + 1] == '_' || ft_isalpha(str[i + 1])))
			{
				start = i + 1;
				i += 1;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				env_var = gc_substr(str, start, i - start);
				value = get_env(env_var);
				gc_free(env_var);

				if (value)
				{
					tmp = gc_strjoin(pre, value);
					gc_free(pre);
					gc_free(value);
					pre = tmp;
				}
				// if no value, we remove the variable and not append anything
				continue ;
			}
			else
			{
				// append one character (with a null terminator by default)
				single_char[0] = str[i];
				tmp = gc_strjoin(pre, single_char);
				gc_free(pre);
				pre = tmp;
				i++;
				continue ;
			}
		}
		// normal character that is not a quote or $
		single_char[0] = str[i];
		tmp = gc_strjoin(pre, single_char);
		gc_free(pre);
		pre = tmp;
		i++;
	}
	return (pre);
}

void	construct_cmd(t_ast_node *node, t_list **words)
{
	t_list	*cmd_elem;
	int		i;

	if (!node)
		return ;
	if (node->type == IO_REDIRECT || node->type == IO_FILE
		|| node->type == IO_HERE || node->type == FILENAME)
		return ;
	if (node->type == WORD)
	{
		cmd_elem = gc_lstnew(env_expander(node->token->value));
		ft_lstadd_back(words, cmd_elem);
		return ;
	}
	i = 0;
	while (i < node->child_count)
	{
		construct_cmd(node->children[i], words);
		i++;
	}
}

char	**build_argv(t_ast_node *simple_command)
{
	t_list	*words;
	t_list	*tmp;
	int		i;
	char	**argv;

	i = 0;
	words = NULL;
	construct_cmd(simple_command, &words);
	tmp = words;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	argv = gc_alloc(sizeof(char *) * (i + 1));
	if (!argv)
	{
		free_t_list(&words);
		return (NULL);
	}
	i = 0;
	while (words)
	{
		argv[i] = words->content;
		i++;
		words = words->next;
	}
	argv[i] = NULL;
	free_t_list(&words);
	if (get_debug())
	{
		printf("command :\n");
		i = 0;
		while (argv[i])
		{
			if (i != 0)
				printf(" -> ");
			printf("%s", argv[i]);
			i++;
		}
		printf("\n");
		//printf("-----------------your expected stuff starts this line\n");
	}
	return (argv);
}
