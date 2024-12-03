/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:28:18 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/30 15:33:30 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		line = gc_next_line(fd, READ_LINE);
		if (!line)
			break ;
		size++;
		gc_free(line);
	}
	gc_next_line(fd, CLEAN_LINE);
	close (fd);
	return (size);
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
		ft_putendl_fd("error opening file", 2);
		return (NULL);
	}
	table = gc_alloc(sizeof(t_entry *) * (size + 1));
	if (!table)
		return (NULL);
	table[size] = NULL;
	while (i < size)
	{
		line = gc_next_line(fd, READ_LINE);
		if (!line)
			break ;
		table[i] = create_entry(line);
		gc_free(line);
		if (!table[i])
		{
			gc_free_array(i, (void **)table);
			close(fd);
			return (NULL);
		}
		i++;
	}
	gc_next_line(fd, CLEAN_LINE);
	close (fd);
	return (table);
}
