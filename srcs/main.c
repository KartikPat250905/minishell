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

t_env	*g_env;
int		g_exit_status;

static void    init_terminal_set(void)
{
    struct termios    term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
        exit(EXIT_FAILURE);
    term.c_lflag &= ~ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
        exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
//int	main (void)
{
	char			*input;
	t_token_stack	*tokens;
	int				ret;
	t_entry			**table;

	(void)av;
	set_debug(false);
	init_terminal_set();
	if (ac > 1)
		set_debug(true);
	tokens = NULL;
	tokens = init_token_stack();
	table = create_table("srcs/parser/parsing-table");
	g_env = fetch_envp(envp);
	g_exit_status = 0;
	while (1)
	{
		get_info()->flag = 0;
		activate_signal_parent();
		int tty_fd = open("/dev/tty", O_RDWR);
		if (tty_fd >= 0)
		{
			dup2(tty_fd, STDIN_FILENO);
			close(tty_fd);
		}
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
		// if (tokens)
		// 	free_tokens()
		//g_env = fetch_envp(envp); //needs to be done every time for now otherwise we segfault
		tokens = lexer(input);
		ret = parsing_main(tokens, table);
		free(input);
		if (ret != 1)
			ft_putendl_fd("-not accepted (parse error)-", 1);
		//gc_free_all();
	}
	clear_history();
	//rl_clear_history();
	rl_free_line_state();
	return (g_exit_status);
}
