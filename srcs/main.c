/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:24:59 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/15 13:47:55 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		return_value;

	(void)argv;
	if (argc != 1)
		return (printf("minishell: requires only one argument\n"), 1);
	return_value = read_lines(envp);
	return (return_value);
}
