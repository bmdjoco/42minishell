/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:24:59 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/26 17:38:50 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	(void)argc;
	(void)argv;
	int ret = read_lines(envp);
	return (ret);
}
