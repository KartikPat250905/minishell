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

void	handle_input(char *input)
{
	add_history(input);
	lexer(input);
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
		g_exit_status = EXIT_SUCCESS;
}

void	main_loop(char *input)
{
	while (1)
	{
		update_envp();
		reset_to_tty();
		input = readline("microshell> ");
		if (!input)
		{
			g_exit_status = EXIT_SUCCESS;
			ft_putstr_fd("bye\n", 1);
			get_info()->break_flag = true;
			break ;
		}
		else if (*input)
			handle_input(input);
		free(input);
		gc_free_all();
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
}

int	main(int ac, char **av, char **envp)
{
	char			*input;

	input = NULL;
	init_terminal_set();
	init_main(ac, av, envp);
	activate_signal_handler();
	main_loop(input);
	if (get_info()->break_flag)
	{
		gc_free_all();
	}
	free_env_list();
	rl_free_line_state();
	return (g_exit_status);
}
