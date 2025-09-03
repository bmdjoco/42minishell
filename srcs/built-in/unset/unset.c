/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:43:41 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/03 11:04:49 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset_var(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->val);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
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
