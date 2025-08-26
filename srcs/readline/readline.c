/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:49:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/26 16:48:35 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_line(char *line, t_env **env)
{
	char	**split;

	if (*line)
		add_history(line);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return ;
	}
	split = mini_split(line);
	if (!split)
	{
		free(line);
		return ;
	}
	echo(split, env);
	free(line);
	free_split(split);
}

/**
 * @brief Lit sur l'entree standard et redirige l'input vers les fonctions
 * @param envp environnement de la machine
 * @return -1 en cas d'echec, 0 si succes
 */
int	read_lines(char **envp)
{
	char	*line;
	t_env	**env;

	env = init_environnement(envp);
	if (!env)
		return (-1);
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(line, env);
	}
	rl_clear_history();
	free_env(env, -9, 2);
	return (0);
}
