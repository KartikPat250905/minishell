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

void	init_terminal_set(void)
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

void	main_loop(char *input)
{
	while (1) //&& !get_info()->break_flag)
	{
		reset_to_tty();
		input = readline("microshell> ");
		if (!input)
		{
			g_exit_status = EXIT_SUCCESS;
			ft_putstr_fd("bye\n", 1);
			break ;
		}
		else if (*input)
		{
			add_history(input);
			lexer(input);
			if (get_info()->break_flag)
				break ;
			if (get_info()->tokens && get_info()->tokens->top->type != END)
			{
				if (parser() == ACCEPT && get_info()->ast)
					execute_ast(get_info()->ast);
				else
				{
					g_exit_status = EXIT_PARSE_ERROR;
					ft_putendl_fd("Parse error", 2);
				}
			}
			else
			{
				g_exit_status = EXIT_SUCCESS;
			}
		}
		gc_free_all();
		free(input);
	}
}

void	init_main(int ac, char **av, char **envp)
{
	t_info	*info;

	(void)av;
	info = get_info();
	ft_bzero(info, sizeof(t_info));
	if (ac > 1)
		info->debug = true;
	fetch_envp(envp);
	update_envp();
}

int	main(int ac, char **av, char **envp)
{
	char			*input;

	input = NULL;
	init_terminal_set();
	init_main(ac, av, envp);
	activate_signal_handler();
	main_loop(input);
	//if (get_gc());
	gc_free_all();
	free_env_list();
	rl_free_line_state();
	return (g_exit_status);
}
