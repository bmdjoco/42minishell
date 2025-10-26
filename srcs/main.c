/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:24:59 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/26 13:23:16 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		return_value;

	(void)argv;
	if (argc != 1)
		return (ft_fprintf(2, "minishell: requires no argument\n"));
	return_value = read_lines(envp);
	return (return_value);
}
