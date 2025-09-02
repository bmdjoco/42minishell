/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:49:44 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/02 12:26:08 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @return renvoie la longueur de la cle
 *
 * @param str variable environnemental (sous forme: USER=test1)
 */
int	size_of_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
/**
 * @return renvoie la longueur de la valeur associe a la cle
 *
 * @param str variable environnemental (sous forme: USER=test1)
 */
int	size_of_val(char *str)
{
	int	i;
	int	l;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	l = 0;
	while (str[i])
	{
		l++;
		i++;
	}
	return (l);
}
/**
 * @brief free en integraliter ou en partis la structure s_env
 *
 * @param env liste de variable environnemental sous forme de structure s_env
 */
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->val);
		free(env);
		env = tmp;
	}
}

/**
 * @brief affiche les variables environnemental
 *
 * @param env liste de variable environnemental sous forme de structure s_env
 */
void	put_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}

void	replace(t_env **env, char *key)
{
	
}
