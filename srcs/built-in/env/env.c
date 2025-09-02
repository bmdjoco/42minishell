/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:38:19 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/02 14:52:20 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Affiche les variables environementales ou une erreur si PATH = NULL
 * @param env Listes des variables environementales
 */
void	builtin_env(t_env *env, int export)
{
	if (!env)
		return ;
	if (export == 0)
	{
		while (env)
		{
			printf("%s=%s\n", env->key, env->val);
			env = env->next;
		}
	}
	else
	{
		while (env)
		{
			printf("export %s=%s\n", env->key, env->val);
			env = env->next;
		}
	}
}
