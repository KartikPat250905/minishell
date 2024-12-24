/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:04:29 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 17:04:33 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "grammer.h"

bool	is_token(char ch, char next)
{
	return (ch == '>' || ch == '<' || ch == '|'
		|| (ch == '>' && next == '>') || (ch == '<' && next == '<'));
}

t_entry	*create_entry(char *line)
{
	char	**splitted;
	int		n;
	t_entry	*entry;

	splitted = gc_split(line, ' ', &n);
	if (!splitted)
		return (NULL);
	entry = gc_alloc(sizeof(t_entry));
	if (!entry)
	{
		gc_free_array(n, (void **)splitted);
		return (NULL);
	}
	entry->state = ft_atoi(splitted[0]);
	entry->token_type = ft_atoi(splitted[1]);
	entry->action = ft_atoi(splitted[2]);
	entry->go_to = ft_atoi(splitted[3]);
	entry->reduce = ft_atoi(splitted[4]);
	gc_free_array(n, (void **)splitted);
	return (entry);
}

t_entry	**create_table(void)
{
	int		i;
	char	*line;
	t_entry	**table;

	i = 0;
	table = gc_alloc(sizeof(t_entry *) * (100 + 1));
	if (!table)
		return (NULL);
	while (i < 100)
	{
		line = get_line(i);
		if (!line)
			break ;
		table[i] = create_entry(line);
		if (!table[i])
		{
			gc_free_array(i, (void **)table);
			return (NULL);
		}
		i++;
	}
	table[i] = NULL;
	return (table);
}
