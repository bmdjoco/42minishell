/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:43:41 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/07 12:30:44 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset_var(t_env *env, char *key)
{
	t_env	*tmp;

	if (!env || !key)
		return ;
	tmp = env;
	while (tmp)
	{
		if (tmp->key && !ft_strcmp(tmp->key, key))
		{
			free(tmp->key);
			tmp->key = NULL;
			if (tmp->val)
			{
				free(tmp->val);
				tmp->val = NULL;
			}
			return ;
		}
		tmp = tmp->next;
	}
}

/**
 * @brief Supprime une variable de l'environnement
 * @param env liste de variable environnemental sous forme de structure s_env
 * @param split ensemble de chaines de caracteres de l'input
 */
void	unset(t_env	**env, char **split)
{
	int	i;

	i = 0;
	if (!split[i])
		return ;
	while (split[i])
	{
		unset_var(*env, split[i]);
		i++;
	}
}
