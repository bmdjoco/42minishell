/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:11:41 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/22 14:57:47 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Initialiser la structure de variable environnemental
 *
 * @return renvoie le pointeur vers la structure ou NULL en cas s'erreur
 */
t_env	**init_environnement(char **envp)
{
	int		i;
	t_env	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(t_env *) * (i + 1));
	if (!env)
		return (ft_putstr_fd("Error: 1\n", 2), NULL);
	i = -1;
	while (envp[++i])
	{
		env[i] = malloc(sizeof(t_env));
		if(!env[i])
			return (free_env(env, i - 1, 2), ft_putstr_fd("Error: 2\n", 2), NULL);
		env[i]->key = ft_strndup(envp[i], size_of_key(envp[i]));
		if(!env[i]->key)
			return (free_env(env, i, 0), ft_putstr_fd("Error: 3\n", 2), NULL);
		env[i]->val = ft_strndup(&envp[i][size_of_key(envp[i]) + 1], size_of_val(envp[i]));
		if(!env[i]->val)
			return (free_env(env, i, 1), ft_putstr_fd("Error: 4\n", 2), NULL);
	}
	env[i] = NULL;
	return (env);
}
