/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:02:58 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/28 16:37:25 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

void	signal_handler(int sig)
{
	g_received_signal = sig;
}

void	sigquit_handler(int sig)
{
	g_received_signal = 0;
	signal_handler(sig + 128);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_handler(int sig)
{
	g_received_signal = 0;
	signal_handler(sig + 128);
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_distributor(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_distributor(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
