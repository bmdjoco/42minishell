/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:43:41 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/05 14:57:32 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset_var(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !*env || !key)
		return ;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
			return ;
		}
		prev = tmp;
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
		unset_var(env, split[i]);
		i++;
	}
}
