/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:38:19 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/16 13:33:17 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_export(t_env *env)
{
	int	len;

	while (env)
	{
		if (!env->val)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 2);
		}
		else
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "=", 1);
			len = ft_strlen(env->val);
			write(STDOUT_FILENO, env->val, len);
			write(STDOUT_FILENO, "\n", 2);
		}
		env = env->next;
	}
}

static void	print_env(t_env *env)
{
	int	len;

	while (env)
	{
		if (!env->val)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, "export ", 7);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 2);
		}
		else
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, "export ", 7);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "=", 1);
			len = ft_strlen(env->val);
			write(STDOUT_FILENO, env->val, len);
			write(STDOUT_FILENO, "\n", 2);
		}
		env = env->next;
	}
}

/**
 * @brief Affiche les variables environementales ou une erreur si PATH = NULL
 * @param env Listes des variables environementales
 */
void	builtin_env(t_env *env, int export)
{
	if (!env)
		return ;
	if (export == 0)
		print_export(env);
	else
		print_env(env);
}
