/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:42:45 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/30 12:02:51 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_delim(char **split, int index, int index2)
{
	int	i;
	int	j;
	int	cmd_i;

	i = 0;
	j = 0;
	cmd_i = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], "|"))
		{
			cmd_i++;
			i++;
			continue ;
		}
		if (cmd_i == index && !ft_strcmp(split[i], "<<"))
		{
			if (split[i + 1] && index2 == j)
				return (ft_strdup(split[i + 1]));
			j++;
		}
		i++;
	}
	return (NULL);
}

char	**split_range(char **split, int start, int end)
{
	int		len;
	int		i;
	char	**new;

	len = end - start;
	new = ft_calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(split[start + i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**cmd_split(char **split, int index)
{
	int	i;
	int	cmd_i;
	int	start;
	int	count;

	1 && (i = 0, cmd_i = 0, start = 0);
	while (split[i])
	{
		if (cmd_i == index)
			break ;
		if (!ft_strcmp(split[i], "|"))
		{
			cmd_i++;
			start = i + 1;
		}
		i++;
	}
	count = 0;
	while (split[i] && ft_strcmp(split[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (split_range(split, start, start + count));
}

int	solo(char **split, t_env *env, int *herefd, t_pipes *pipes)
{
	pid_t	pid;
	int		exit_code;

	if (pipes->docs > 0)
	{
		pid = fork();
		if (pid == -1)
			return (free(pipes), perror("minishell: "), -1);
		if (pid == 0)
		{
			dup2(herefd[0], STDIN_FILENO);
			close(herefd[0]);
			free(herefd);
			exit_code = do_redirections(split, 0, env, pipes);
			free_split(split);
			free_env(env);
			exit (exit_code);
		}
		free(pipes);
		close(herefd[0]);
		free(herefd);
		return (get_code(pid));
	}
	return (do_redirections(split, 0, env, pipes));
}
