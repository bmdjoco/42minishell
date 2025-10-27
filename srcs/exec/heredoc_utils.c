/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:27:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/27 12:27:28 by miltavar         ###   ########.fr       */
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
	{
		exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_fprintf(2, "Quit (core dumped)\n");
	}
	else
		exit_code = 1;
	g_received_signal = exit_code;
	return (exit_code);
}

void	cl_fd(int *here_fd, int index)
{
	int	i;

	if (!here_fd)
		return ;
	i = 0;
	while (i < index)
	{
		if (here_fd[i] != -1)
			close(here_fd[i]);
		i++;
	}
}

int	create_docs(t_doc *doc, int *herefd, t_pipes *pipes, int index)
{
	int	err;
	int	nb;
	int	i;

	i = 0;
	nb = has_here(doc->og_split, index);
	while (i < nb)
	{
		doc->delim = get_delim(doc->og_split, index, i);
		doc->i = index;
		err = do_heredoc(doc, herefd, pipes);
		free(doc->delim);
		if (i < nb - 1)
			close(herefd[doc->i]);
		if (err != 0)
		{
			return (cl_fd(herefd, index + 1),
				free(herefd), free(doc), pipes->err = err, err);
		}
		i++;
	}
	return (0);
}

int	*here_prep(char **split, t_env *env, t_pipes *pipes)
{
	int		*here_fd;
	int		i;
	t_doc	*doc;

	if (pipes->docs == 0)
		return (NULL);
	doc = malloc(sizeof(t_doc));
	if (!doc)
		return (NULL);
	1 && (doc->env_dup = env, doc->og_split = split,
		here_fd = malloc(sizeof(int) * 1024), i = 0);
	if (!here_fd)
		return (free(doc), NULL);
	while (i < 1024)
	{
		if (has_here(split, i) != 0)
		{
			if (create_docs(doc, here_fd, pipes, i) != 0)
				return (NULL);
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
	int	res;
	int	cmd_i;

	i = 0;
	cmd_i = 0;
	res = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], "|"))
		{
			cmd_i++;
			i++;
			continue ;
		}
		if (cmd_i == index && !ft_strcmp(split[i], "<<"))
			res++;
		i++;
	}
	return (res);
}
