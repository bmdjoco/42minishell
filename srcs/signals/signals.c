/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:02:58 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/26 14:33:01 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t g_received_signal = 0;

void signal_handler(int sig)
{
	if (sig == SIGINT)
		g_received_signal = SIGINT;
	else if (sig == SIGQUIT)
		g_received_signal = SIGQUIT;
}
