/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:38:19 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/01 14:57:29 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Affoiche les variables environementales ou une erreur si PATH = NULL
 * @param env Listes des variables environementales
 */
void	builtin_env(t_env *env)
{
	char	*temp;

	temp = get_env_value(env, "PATH");
	if (!temp)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return ;
	}
	free(temp);
	put_env(env);
}
