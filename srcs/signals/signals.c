/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:01:17 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 17:01:18 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_parent(int sig)
{
	//printf("here in sig_handler_parent\n");
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_exit_status = 131;
	}
}

void	activate_signal_parent(void)
{
	signal(SIGINT, sig_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
}

void	activate_signal_handler(void)
{
	//printf("I am activating stuff");
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

void	hd_sig_handler(int sig)
{
	//printf("Here in hd_sig_handler\n");
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		int null_fd = open("/dev/null", O_RDONLY);
		if (null_fd >= 0)
		{
			dup2(null_fd, STDIN_FILENO);
			close(null_fd);
		}
		//write(1, "\n", 1);
		//close(0);
		g_exit_status = 130;
		//printf("i assigned %i to exit status", g_exit_status);
	}
}

void	activate_hd_signal_handler(void)
{
	signal(SIGINT, hd_sig_handler);
	signal(SIGQUIT, hd_sig_handler);
}

void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
