/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:27:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/21 18:59:32 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_code(pid_t pid)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	exit_code = g_received_signal;
	return (exit_code);
}

void	process_child_status(int status, int *first_error,
	int *exit_code, int is_last)
{
	int	code;

	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		if (code != 0 && *first_error == 0)
			*first_error = code;
		if (is_last)
			*exit_code = code;
	}
	else if (WIFSIGNALED(status))
	{
		code = 128 + WTERMSIG(status);
		if (*first_error == 0)
			*first_error = code;
		if (is_last)
			*exit_code = code;
	}
}

void	free_close(int *here_fd, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		close(here_fd[i]);
		i++;
	}
}

int	*here_prep(char **split, t_env *env, int nb)
{
	int	*here_fd;
	int		i;
	char	**cmd;
	char	*delim;
	int		err;

	here_fd = malloc(sizeof(int) * nb);
	if (!here_fd)
		return (signal_handler(1), NULL);
	i = 0;
	while (i < nb)
	{
		if (has_here(split, i))
		{
			cmd = cmd_split(split, i);
			delim = get_delim(split, i);
			err = do_heredoc(cmd, env, delim, &here_fd[i]);
			(free_split(cmd), free(delim));
			if (err == 130)
				return (free_close(here_fd, i), free(here_fd), NULL);
		}
		else
			here_fd[i] = -1;
		i++;
	}
	return (here_fd);
}

int	has_here(char **split, int index)
{
	int	i;
	int	cmd_i;

	i = 0;
	cmd_i = 0;
	while (split[i])
	{
		if (!strcmp(split[i], "|"))
		{
			cmd_i++;
			i++;
			continue ;
		}
		if (cmd_i == index && !ft_strcmp(split[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

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
