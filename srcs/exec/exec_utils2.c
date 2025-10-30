/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:27:33 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/30 12:28:13 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*final_path(char **argv, char **envp)
{
	char	*correct;

	correct = NULL;
	if (argv[0][0] != '/' && argv[0][0] != '.' && argv[0][0] != '~')
	{
		correct = correct_path(argv, envp);
		if (!correct)
			return (NULL);
	}
	else
	{
		if (access(argv[0], X_OK) != 0)
			return (NULL);
		correct = ft_strdup(argv[0]);
	}
	return (correct);
}

char	*concat(char *key, char *val)
{
	char	*res;
	char	*key2;
	char	*val2;
	char	*tmp;

	if (!val)
		return (ft_strdup(key));
	key2 = ft_strdup(key);
	if (!key2)
		return (NULL);
	val2 = ft_strdup(val);
	if (!val2)
		return (free(key2), NULL);
	tmp = ft_strjoin(key2, "=");
	if (!tmp)
		return (free(val2), NULL);
	free(key2);
	key2 = tmp;
	res = ft_strjoin(key2, val2);
	if (!res)
		return (free(key2), free(val2), NULL);
	free(key2);
	free(val2);
	return (res);
}

char	*grab_line(t_env *env, int j)
{
	char	*res;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (i == j)
		{
			res = concat(tmp->key, tmp->val);
			if (!res)
				return (NULL);
			return (res);
		}
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int	get_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**create_envp(t_env *env)
{
	char	**envpdup;
	int		i;
	int		size;

	if (!env)
		return (NULL);
	size = get_size(env);
	if (size <= 0)
		return (NULL);
	envpdup = ft_calloc(size + 1, 8);
	if (!envpdup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envpdup[i] = grab_line(env, i);
		if (!envpdup[i])
			return (free_split(envpdup), NULL);
		i++;
	}
	envpdup[i] = NULL;
	return (envpdup);
}
