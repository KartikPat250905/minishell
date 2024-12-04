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

int	main(int ac, char **av, char **envp)
//int	main (void)
{
	char			*input;
	//t_token_stack	*tokens;
	//int				ret;
	//t_entry			**table;
	int				no_of_args;
	char			**args;
	
	g_env = fetch_envp(envp);
	// ft_cd(ac, av);
	// ft_pwd();
	(void)ac;
	(void)av;
	// tokens = NULL;
	// activate_signal_handler();
	// tokens = init_token_stack();
	while (1)
	{
		input = readline("microshell> ");
		if (!input || !ft_strcmp(input, "exit"))
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
		args = ft_split(input, ' ', &no_of_args);
		ft_echo(no_of_args, args);
		ft_env(no_of_args, args);
		ft_export(no_of_args, args);
		// table = create_table("srcs/parser/parsing-table");
		// tokens = lexer(input);
		// ret = parsing_main(tokens, table);
		// free(input);
		// if (ret != 1)
		// 	ft_putendl_fd("-not accepted (parse error)-", 1);
		// gc_free_all();
}
	clear_history();
	//rl_clear_history();
	rl_free_line_state();
	return (0);
}
