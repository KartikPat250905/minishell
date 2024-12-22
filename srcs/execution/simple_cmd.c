/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:53:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/06 10:53:11 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void execute_simple_cmd(t_ast_node *simple_cmd)
{
	char **argv;
	t_exec_info info;

	initialize_exec_info(&info);
	activate_signal_handler();
	gather_redirects(simple_cmd, &info);
	if (!get_info()->flag)
		return ;
	argv = build_argv(simple_cmd);
	if (!argv || !argv[0])
	{
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	if (is_builtin(argv[0]))
	{
		execute_builtin_cmd(argv, &info);
		return ;
	}
	else
		execute_external_cmd(argv, &info);
	// gc_free_array((void **)argv, //length of argv);
}

void execute_simple_piped_cmd(char **argv)
{
	int status;

	if (!argv || !argv[0])
	{
		g_exit_status = EXIT_FAILURE;
		exit(g_exit_status);
	}
	if (is_builtin(argv[0]))
	{
		status = execute_builtin(argv);
		exit(status);
	}
	resolve_and_exec_cmd(argv);
	// this should not happen
}
