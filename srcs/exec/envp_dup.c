/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:39:12 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/07 12:39:21 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_size(t_env *env)
{
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->val)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

static char	*create_env_line(t_env *node)
{
	char	*line;
	char	*result;

	line = ft_strjoin(node->key, "=");
	if (!line)
		return (NULL);
	result = ft_strjoin(line, node->val);
	free(line);
	return (result);
}

static int	fill_envp(char **envpdup, t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->key && tmp->val)
		{
			envpdup[i] = create_env_line(tmp);
			if (!envpdup[i])
				return (-1);
			i++;
		}
		tmp = tmp->next;
	}
	envpdup[i] = NULL;
	return (0);
}

char	**create_envp(t_env *env)
{
	char	**envpdup;
	int		size;

	size = count_env_size(env);
	if (size == 0)
		return (NULL);
	envpdup = ft_calloc(size + 1, sizeof(char *));
	if (!envpdup)
		return (perror("minishell"), NULL);
	if (fill_envp(envpdup, env) == -1)
		return (free_split(envpdup), NULL);
	return (envpdup);
}
