/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:42:45 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/22 15:52:30 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_delim(char **split, int index)
{
	int	i;
	int	cmd_i;

	i = 0;
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
			if (split[i + 1])
				return (ft_strdup(split[i + 1]));
			else
				return (NULL);
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

int	solo(char **split, t_env *env, int *herefd)
{
	pid_t	pid;
	int		exit_code;

	if (herefd && herefd[0] != -1)
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell: "), -1);
		if (pid == 0)
		{
			dup2(herefd[0], STDIN_FILENO);
			close(herefd[0]);
			free(herefd);
			exit_code = do_redirections(split, env);
			free_env(env);
			free_split(split);
			exit (exit_code);
		}
		close(herefd[0]);
		free(herefd);
		return (get_code(pid));
	}
	return (free(herefd), do_redirections(split, env));
}
