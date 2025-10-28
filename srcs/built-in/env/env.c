/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:38:19 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/28 15:39:46 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_env(t_env *env)
{
	int	len;

	while (env)
	{
		if (!env->val && ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 2);
		}
		else if (ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "=", 1);
			len = ft_strlen(env->val);
			write(STDOUT_FILENO, env->val, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

static void	print_export(t_env *env)
{
	int	len;

	while (env)
	{
		if (!env->val && ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, "export ", 7);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (ft_strcmp("?", env->key) != 0)
		{
			len = ft_strlen(env->key);
			write(STDOUT_FILENO, "export ", 7);
			write(STDOUT_FILENO, env->key, len);
			write(STDOUT_FILENO, "=", 1);
			len = ft_strlen(env->val);
			write(STDOUT_FILENO, env->val, len);
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

/**
 * @brief Affiche les variables environementales ou une erreur si PATH = NULL
 * @param env Listes des variables environementales
 */
int	builtin_env(t_env *env, int export, char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (ft_strcmp(split[i], "env") != 0)
			return (ft_fprintf(2, "minishell: '%s': No such file or directory\n",
					split[i]), 127);
		i++;
	}
	if (!env)
		return (1);
	if (export == 1)
		print_export(env);
	else
		print_env(env);
	return (0);
}
