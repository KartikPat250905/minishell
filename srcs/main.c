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


int	main(int ac, char **av, char **envp)
//int	main (void)
{
	char			*input;
	int				ret;
	t_entry			**table;
	t_info			*info;

	info = gc_alloc(sizeof(t_info));
	ft_bzero(info, sizeof(t_info));
	set_info(info);
	(void)av;
	if (ac > 1)
		info->debug = true; //set_debug(true);
	info->tokens = init_token_stack();
	info->env = fetch_envp(envp);
	table = create_table("srcs/parser/parsing-table");
	activate_signal_handler();
	while (1)
	{
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
		info->tokens = lexer(input);
		ret = parsing_main(info->tokens, table);
		free(input);
		if (ret != 1)
			ft_putendl_fd("-not accepted (parse error)-", 1);
		//gc_free_all();
	}
	clear_history();
	//rl_clear_history();
	rl_free_line_state();
	return (0);
}
