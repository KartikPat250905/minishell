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
	pid_t pid;
	char *path;
	char **paths;
	int status;
	int n;
	t_exec_info info;
	int original_in;
	int original_out;

	info.heredoc_fd = -1;
	info.redir_list = NULL;
	activate_signal_handler();
	gather_redirects(simple_cmd, &info);
	if (!get_info()->flag)
		return;
	argv = build_argv(simple_cmd);
	// if (!argv) //either no command or unclosed quotes
	//	return ;
	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	if (!original_in || !original_out)
	{
		return;
	}
	if (argv && is_builtin(argv[0]))
	{
		if (info.heredoc_fd != -1)
		{
			dup2(info.heredoc_fd, STDIN_FILENO);
			close(info.heredoc_fd);
		}
		apply_normal_redirections(info.redir_list);
		g_exit_status = execute_builtin(argv);
		dup2(original_in, STDIN_FILENO);
		dup2(original_out, STDOUT_FILENO);
		close(original_in);
		close(original_out);
		return;
	}
	else if (argv)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return; // not sure if we should return or exit
		}
		else if (pid == 0) // child
		{
			activate_signal_handler();
			if (info.heredoc_fd != -1)
			{
				dup2(info.heredoc_fd, STDIN_FILENO);
				close(info.heredoc_fd);
			}
			apply_normal_redirections(info.redir_list);
			path = get_env("PATH");
			if (is_cmd_already_path(argv[0]))
				path = argv[0];
			else
			{
				if (!path)
				{
					ft_putstr_fd("microshell: ", 2);
					ft_putstr_fd(argv[0], 2);
					ft_putendl_fd(": No such file or directory", 2);
					g_exit_status = 127;
					exit(g_exit_status); // is this the correct exit code?
				}
				paths = gc_split(path, ':', &n);
				path = look_for_cmd(argv[0], paths);
				gc_free_array(n, (void **)paths);
			}
			if (!path)
			{
				ft_putstr_fd(argv[0], 2);
				ft_putendl_fd(": command not found", 2);
				g_exit_status = 127;
				exit(g_exit_status); // is this the correct exit code?
			}
			if (execve(path, argv, get_info()->envp) == -1)
			{
				perror("execve");
				g_exit_status = 126;
				exit(g_exit_status); // is this the correct exit code?
			}
		}
		else // parent
		{
			ignore_signals();
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				int signal_num = WTERMSIG(status);
				g_exit_status = 128 + signal_num;
			}
		}
	}
	// gc_free_array((void **)argv, //length of argv);
}

void execute_simple_piped_cmd(char **argv)
{
	char *path;
	char **paths;
	int status;
	int n;

	if (!argv || !argv[0])
		exit(EXIT_FAILURE);

	if (is_builtin(argv[0]))
	{
		status = execute_builtin(argv);
		exit(status);
	}
	path = get_env("PATH");
	if (is_cmd_already_path(argv[0]))
		path = argv[0];
	else
	{
		if (!path)
		{
			ft_putstr_fd("microshell: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(127); // is this the correct exit code?
		}
		paths = gc_split(path, ':', &n);
		path = look_for_cmd(argv[0], paths);
		gc_free_array(n, (void **)paths);
	}
	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127); // is this the correct exit code?
	}
	if (execve(path, argv, get_info()->envp) == -1)
	{
		perror("execve");
		exit(126); // is this the correct exit code?
	}
	// this should not happen
}
