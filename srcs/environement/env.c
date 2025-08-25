/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:11:41 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/25 16:04:55 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/**
 * @brief renvoie la valeur correspondant a la cle passer en argument
 *
 * @param env liste de variable environnemental sous forme de structure s_env
 * @param key cle correspondant a la valeur rechercher
 * @return renvoie une chaine de charactere correspondant a la valleur ou NULL en cas d'erreur
 */
char	*get_env_value(t_env **env, char *key)
{
	int	i;

	if (!key)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (strcmp(key, env[i]->key) == 0)
			return (ft_strdup(env[i]->val));
		i++;
	}
	return (NULL);
}

int	set_env_value(t_env **env, char *key, char *val)
{
	int	i;
	char	*tmp;

	i = 0;
	if (!key || !val)
		return (0);
	while (env[i])
	{
		if (strcmp(key, env[i]->key) == 0)
		{
			tmp = env[i]->val;
			env[i]->val = NULL;
			env[i]->val = ft_strdup(env[i]->val);
			if(!env[i]->val)
				{

				}
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}
