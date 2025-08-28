/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:25:04 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/28 14:27:46 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clear_current(char *path)
{
	char	*tmp_path;
	char	*tmp;

	tmp_path = ft_strdup(path);
	if (tmp_path && ft_strfind(tmp_path, "./") > 0)
	{
		tmp = ft_strchr_and_cut(tmp_path, "./");
		if (!tmp)
			return (NULL);
		free(tmp_path);
		tmp_path = tmp;
	}
	if (tmp_path && ft_strncmp(&tmp_path[sizeof(tmp_path) - 2], "/.", 2))
	{
		free(tmp_path);
		tmp_path = ft_strchr_and_cut(path, "./");
	}
	if (!tmp_path)
		return (NULL);
}

static char	*clean_absolute_path(t_env *env, char *path)
{
	char	*tmp_path;

	tmp_path = ft_strdup(path);
	
}

/**
 * @brief transforme un path relatif en absolue puis appelle la fonction de clean des path absolue
 */
static char	*clean_relative_path(t_env *env, char *path)
{
	char	*n_path;
	char	*home;
	char	*res;

	home = get_env_value(env, "HOME");
	if (!home)
		return (ft_fprintf(2, "minishell: Error env[HOME] not found\n"), NULL);
	n_path = ft_strjoin_w_sep(home, path, '/');
	if (!n_path)
		return (ft_fprintf(2, "minishell: Error join with separator fail\n"), NULL);
	res = clean_absolute_path(env, n_path);
	if (!res)
		return (NULL);
	free(home);
	free(n_path);
	return (res);
}

/**
 * @brief tranforme le path passer en parametre en passe absolu sans .. ou .
 */
char	*get_clean_abs_path(t_env *env, char *path)
{
	char *res;

	if (path[0] == '/')
	{
		if (nb_of_move(path) >= 0)
		{
			res = calloc(2, sizeof(char));
			if (!res)
				return (ft_fprintf(2, "minishell: calloc error\n"), NULL);
			res[0] = '/';
			return (res);
		}
		return (clean_absolute_path(env, path));
	}
	(void) res;
	return (clean_relative_path(env, path));
}
