/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:24:59 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/07 16:04:20 by bdjoco           ###   ########.fr       */
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
