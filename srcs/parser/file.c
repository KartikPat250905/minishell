/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:28:18 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 15:58:16 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_table_size(char *filename)
{
	int		size;
	int		fd;
	char	*line;

	size = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		size++;
		free(line);
	}
	close (fd);
	return (size);
}

t_entry	*create_entry(char *line)
{
	char	**splitted;
	int		n;
	t_entry	*entry;

	splitted = ft_split(line, ' ', &n);
	if (!splitted)
		return (NULL);
	entry = malloc(sizeof(t_entry));
	if (!entry)
	{
		while (n--)
			free(splitted[n]);
		free(splitted);
		return (NULL);
	}
	entry->state = ft_atoi(splitted[0]);
	entry->token_type = ft_atoi(splitted[1]);
	entry->action = ft_atoi(splitted[2]);
	entry->go_to = ft_atoi(splitted[3]);
	entry->reduce = ft_atoi(splitted[4]);
	while (n--)
		free(splitted[n]);
	free(splitted);
	return (entry);
}

t_entry	**create_table(char *filename)
{
	int		i;
	int		size;
	int		fd;
	char	*line;
	t_entry	**table;

	i = 0;
	size = get_table_size(filename);
	fd = open(filename, O_RDONLY);
	if (size <= 0 || fd == -1)
	{
		ft_putendl_fd("error", 2);
		exit(EXIT_FAILURE);
	}
	table = malloc(sizeof(t_entry *) * size);
	if (!table)
		exit(EXIT_FAILURE);
	while (i < size)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		table[i] = create_entry(line);
		free(line);
		if (!table[i])
		{
			while (i-- > 0)
				free(table[i]);
			free(table);
			close(fd);
			exit (EXIT_FAILURE);
		}
		i++;
	}
	close (fd);
	return (table);
}
