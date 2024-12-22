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

//t_env	*g_env;
int	g_exit_status;

static void	init_terminal_set(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
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
}

void	main_loop(t_entry **table, t_info *info, char *input, int ret)
{
	while (1)
	{
		info->flag = 1;
		activate_signal_parent();
		reset_to_tty();
		input = readline("microshell> ");
		if (!input)
		{
			printf("Exit\n");
			break ;
		}
		if (!*input)
			continue ;
		if (*input)
			add_history(input);
		info->tokens = lexer(input);
		// if (tokens)
		// 	free_tokenstack()
		ret = parsing_main(info->tokens, table);
		free(input);
		if (ret != 1)
			ft_putendl_fd("-not accepted (parse error)-", 1);
		//gc_free_all();
	}
}

int	main(int ac, char **av, char **envp)
//int	main (void)
{
	char			*input;
	int				ret;
	t_entry			**table;
	t_info			*info;

	info = get_info();
	input = NULL;
	ret = 1;
	ft_bzero(info, sizeof(t_info));
	(void)av;
	init_terminal_set();
	if (ac > 1)
		info->debug = true;
	info->tokens = init_token_stack();
	fetch_envp(envp);
	update_envp();
	table = create_table();
	activate_signal_handler();
	main_loop(table, info, input, ret);
	//clear_history();
	//rl_clear_history();
	rl_free_line_state();
	return (g_exit_status);
}
