/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:42:38 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/25 11:42:39 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

void	sig_handler_child(int sig);
void	activate_signal_handler(void);
void	ignore_signals(void);
int		get_exit_status(int status);
void	hd_sig_handler(int sig);
void	activate_hd_signal_handler(void);
void	restore_default_signals(void);
void	activate_signal_parent(void);
void	free_exit(int sig);

#endif
