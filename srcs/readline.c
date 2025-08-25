/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:49:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/25 13:58:20 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_lines(char **envp)
{
	char	*line;
	char	**split;
	t_env	**env;

	env = init_environnement(envp);
	if (!env)
		return (-1);
	while (1)
	{
		line = readline("minishell");
		if (!line)
			return (perror("minishell: failed to read\n"), 127);
		split = mini_split(line);
		if (!split)
			return (-1);
		// exec
		free(line);
		free_split(split);
	}
	free_env(env, -9, 2);
}
