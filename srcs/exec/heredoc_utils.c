/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:27:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/22 15:52:21 by miltavar         ###   ########.fr       */
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

void	close_fds(int *here_fd, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		close(here_fd[i]);
		i++;
	}
}

int	*here_prep(char **split, t_env *env, int nb, t_pipes *pipes)
{
	int	*here_fd;
	int		i;
	int		err;
	t_doc	*doc;

	doc = malloc(sizeof(t_doc));
	if (!doc)
		return (NULL);
	doc->env_dup = env;
	doc->og_split = split;
	here_fd = malloc(sizeof(int) * nb);
	if (!here_fd)
		return (signal_handler(1), NULL);
	i = 0;
	while (i < nb)
	{
		if (has_here(split, i))
		{
			doc->cmd = cmd_split(split, i);
			doc->delim = get_delim(split, i);
			err = do_heredoc(doc, here_fd, i, pipes);
			(free_split(doc->cmd), free(doc->delim));
			if (err == 130)
				return (close_fds(here_fd, i + 1), free(here_fd), NULL);
		}
		else
			here_fd[i] = -1;
		i++;
	}
	return (free(doc), here_fd);
}

int	has_here(char **split, int index)
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
			return (1);
		i++;
	}
	return (0);
}
