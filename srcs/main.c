/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:40:50 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/30 18:01:47 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

int	g_exit_status;

static void	init_terminal_set(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		gc_free_all();
		free_env_list();
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		gc_free_all();
		free_env_list();
		exit(EXIT_FAILURE);
	}
}

void	reset_to_tty(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd >= 0)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	get_info()->flag = 1;
	activate_signal_parent();
}

void	main_loop(t_entry **table, char *input)
{
	while (1)
	{
		reset_to_tty();
		input = readline("microshell> ");
		if (!input)
		{
			printf("Exit\n");
			free(input);
			g_exit_status = 0;
			break ;
		}
		if (*input)
		{
			add_history(input);
			get_info()->tokens = lexer(input);
			if (get_info()->tokens)
			{
				if (parsing_main(get_info()->tokens, table) == ACCEPT)
					execute_ast(get_info()->ast);
			}
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*input;
	t_entry			**table;
	t_info			*info;

	(void)av;
	input = NULL;
	info = get_info();
	ft_bzero(info, sizeof(t_info));
	if (ac > 1)
		info->debug = true;
	info->tokens = gc_alloc(sizeof(t_token_stack));
	fetch_envp(envp);
	update_envp();
	table = create_table();
	init_terminal_set();
	activate_signal_handler();
	main_loop(table, input);
	gc_free_all();
	free_env_list();
	rl_free_line_state();
	return (g_exit_status);
}
