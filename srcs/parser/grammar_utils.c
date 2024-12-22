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

bool is_token(char ch, char next)
{
	return (ch == '>' || ch == '<' || ch == '|' ||
			(ch == '>' && next == '>') || (ch == '<' && next == '<'));
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
	table[100] = NULL;
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
	return (table);
}

int	get_non_terminal(int rule_number)
{
    switch (rule_number)
    {
		case 0: return ACCEP; // Rule 0: pipe_sequence → simple_command
        case 1: return PIPE_SEQ; // Rule 1: pipe_sequence → simple_command
        case 2: return PIPE_SEQ; // Rule 2: pipe_sequence → pipe_sequence T_PIPE simple_command
        case 3: return SIMPLE_CMD; // Rule 3: simple_command → cmd_prefix cmd_word cmd_suffix
        case 4: return SIMPLE_CMD; // Rule 4: simple_command → cmd_prefix cmd_word
        case 5: return SIMPLE_CMD; // Rule 5: simple_command → cmd_prefix
        case 6: return SIMPLE_CMD; // Rule 6: simple_command → cmd_name cmd_suffix
        case 7: return SIMPLE_CMD; // Rule 7: simple_command → cmd_name
        case 8: return CMD_NAME; // Rule 8: cmd_name → T_WORD
        case 9: return CMD_WORD; // Rule 9: cmd_word → T_WORD
        case 10: return CMD_PREFIX; // Rule 10: cmd_prefix → IO_REDIRECT
        case 11: return CMD_PREFIX; // Rule 11: cmd_prefix → cmd_prefix IO_REDIRECT
        case 12: return CMD_SUFFIX; // Rule 12: cmd_suffix → IO_REDIRECT
        case 13: return CMD_SUFFIX; // Rule 13: cmd_suffix → cmd_suffix IO_REDIRECT
        case 14: return CMD_SUFFIX; // Rule 14: cmd_suffix → WORD
        case 15: return CMD_SUFFIX; // Rule 15: cmd_suffix → cmd_suffix WORD
        case 16: return IO_REDIRECT; // Rule 16: io_redirect → io_file
        case 17: return IO_REDIRECT; // Rule 17: io_redirect → io_here
        case 18: return IO_FILE; // Rule 18: io_file → '<' filename
        case 19: return IO_FILE; // Rule 19: io_file → '>' filename
        case 20: return IO_FILE; // Rule 20: io_file → DGREAT filename
        case 21: return FILENAME; // Rule 21: filename → WORD
        case 22: return IO_HERE; // Rule 22: DLESS → here_end
        case 23: return HERE_END; // Rule 22: here_end → WORD
        default:
            ft_putendl_fd("Error: Invalid rule number", 2);
            return -1; // Indicate error
    }
}

const char* get_symbol_name(int type)
{
    switch (type)
    {
        // Non-terminals
        case 9: return "$accept";
        case 10: return "pipe_sequence";
        case 11: return "simple_command";
        case 12: return "cmd_name";
        case 13: return "cmd_word";
        case 14: return "cmd_prefix";
        case 15: return "cmd_suffix";
        case 16: return "io_redirect";
        case 17: return "io_file";
        case 19: return "io_here";
        case 21: return "filename";
        case 23: return "here_end";
        // Terminals
        case 0: return "END";
        case 60: return "'<'";
        case 62: return "'>'";
        case 124: return "'|'";
        case 256: return "ERROR";
        case 258: return "WORD";
        case 259: return "DLESS";
        case 260: return "DGREAT";
        default: return "UNKNOWN";
    }
}
