/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:41:47 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/02 18:41:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "grammer.h"
#include "minishell.h"

int	map_rule_to_non_terminal(int rule_number)
{
	if (rule_number == 1 || rule_number == 2)
		return (PIPE_SEQ);
	else if (rule_number >= 3 && rule_number <= 7)
		return (SIMPLE_CMD);
	else if (rule_number == 8)
		return (CMD_NAME);
	else if (rule_number == 9)
		return (CMD_WORD);
	else if (rule_number == 10 || rule_number == 11)
		return (CMD_PREFIX);
	else if (rule_number >= 12 && rule_number <= 15)
		return (CMD_SUFFIX);
	else if (rule_number == 16 || rule_number == 17)
		return (IO_REDIRECT);
	else if (rule_number >= 18 && rule_number <= 20)
		return (IO_FILE);
	else if (rule_number == 21)
		return (FILENAME);
	else if (rule_number == 22)
		return (IO_HERE);
	else if (rule_number == 23)
		return (HERE_END);
	else
		return (-1);
}

int	get_non_terminal(int rule_number)
{
	int	result;

	result = map_rule_to_non_terminal(rule_number);
	if (rule_number == 0)
		return (ACCEP);
	if (result == -1)
	{
		ft_putendl_fd("Error: Invalid rule number", 2);
		return (-1);
	}
	return (result);
}

const char	*get_non_terminal_name(int type)
{
	if (type == 9)
		return ("$accept");
	else if (type == 10)
		return ("pipe_sequence");
	else if (type == 11)
		return ("simple_command");
	else if (type == 12)
		return ("cmd_name");
	else if (type == 13)
		return ("cmd_word");
	else if (type == 14)
		return ("cmd_prefix");
	else if (type == 15)
		return ("cmd_suffix");
	else if (type == 16)
		return ("io_redirect");
	else if (type == 17)
		return ("io_file");
	else if (type == 19)
		return ("io_here");
	else if (type == 21)
		return ("filename");
	else if (type == 23)
		return ("here_end");
	return ("UNKNOWN");
}

const char	*get_terminal_name(int type)
{
	if (type == 0)
		return ("END");
	else if (type == 60)
		return ("'<>'");
	else if (type == 62)
		return ("'>'");
	else if (type == 124)
		return ("'|'");
	else if (type == 256)
		return ("ERROR");
	else if (type == 258)
		return ("WORD");
	else if (type == 259)
		return ("DLESS");
	else if (type == 260)
		return ("DGREAT");
	else
		return ("UNKNOWN");
}

const char	*get_symbol_name(int type)
{
	if (type >= 9 && type <= 23)
	{
		return (get_non_terminal_name(type));
	}
	else
	{
		return (get_terminal_name(type));
	}
}
