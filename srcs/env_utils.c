/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:49:44 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/22 15:07:45 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
 * @param i indice de depart de liberage de la liste (-9 si toute la liste)
 * @param f indice d'erreur (2 pour key val ainsi que le pointeur, 1 pour key ainsi que le pointeur et 0 pour le pointeur uniquement)
 */
void	free_env(t_env **env, int i, int f)
{
	if (i == -9)
	{
		i = -1;
		while (env[++i])
		{
			free(env[i]->val);
			free(env[i]->key);
			free(env[i]);
		}
	}
	else
		while (i >= 0)
		{
			if (f >= 2)
				free(env[i]->val);
			if (f >= 1)
				free(env[i]->key);
			free(env[i]);
			i--;
		}
	free(env);
}

/**
 * @brief affiche les variables environnemental
 *
 * @param env liste de variable environnemental sous forme de structure s_env
 */
void	put_env(t_env **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s=%s\n", env[i]->key, env[i]->val);
		i++;
	}
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

	i = 0;
	while (env[i])
	{
		if (strcmp(key, env[i]->key) == 0)
			return (ft_strdup(env[i]->val));
		i++;
	}
	return (NULL);
}
