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
		cmd_elem = ft_lstnew(env_expander(node->token->value));
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

static int	get_list_size(t_list *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

static void	debug_print_argv(char **argv)
{
	int	i;

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
}

char	**build_argv(t_ast_node *simple_command)
{
	t_list	*words;
	int		i;
	char	**argv;

	words = NULL;
	construct_cmd(simple_command, &words);
	i = get_list_size(words);
	argv = gc_alloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (words)
	{
		argv[i] = words->content;
		i++;
		words = words->next;
	}
	argv[i] = NULL;
	if (get_debug())
		debug_print_argv(argv);
	return (argv);
}
