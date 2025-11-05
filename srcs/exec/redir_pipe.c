/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:40:10 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/05 14:46:17 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first(char **split, t_env *env, t_pipes *pipes, int *here_fd)
{
	pid_t	pid;
	int		pipefd[2];
	int		ext;

	if (pipe(pipefd) == -1)
		return (perror("minishell: "), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipefd[0]), close(pipefd[1]), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (here_fd && here_fd[0] != -1)
			dup2(here_fd[0], STDIN_FILENO);
		1 && (dup2(pipefd[1], STDOUT_FILENO),
			close(pipefd[1]), cl_fd(here_fd, pipes->docs),
			free(here_fd), ext = do_redirections(split, 0, env, pipes),
			free_split(split), free_env(&env), exit (ext), 0);
	}
	close(pipefd[1]);
	if (here_fd && here_fd[0] != -1)
		close(here_fd[0]);
	pipes->oldfd = pipefd[0];
	return (pipes->i++, pid);
}

int	mid(char **split, t_env *env, t_pipes *pip, int *fds)
{
	pid_t	pid;
	int		prevfd;
	int		pipefd[2];
	int		ext;

	prevfd = pip->oldfd;
	if (pipe_fork(pipefd, &pid) == -1)
		return (perror("minishell: "), close(prevfd), -1);
	if (pid == 0)
	{
		if (fds && fds[pip->i] != -1)
			dup2(fds[pip->i], STDIN_FILENO);
		else
			dup2(prevfd, STDIN_FILENO);
		1 && (close(pipefd[0]), dup2(pipefd[1], STDOUT_FILENO),
			close(pipefd[1]), close(prevfd),
			cl_fd(fds, pip->docs), free(fds),
			ext = do_redirections(split, skip_cmd(split, pip->i),
				env, pip), free_split(split), free_env(&env), exit (ext), 0);
	}
	1 && (close(prevfd), close(pipefd[1]));
	if (fds && fds[pip->i] != -1)
		close(fds[pip->i]);
	return (pip->i++, pip->oldfd = pipefd[0], pid);
}

int	last(char **split, t_env *env, t_pipes *pipes, int *here_fd)
{
	pid_t	pid;
	int		ext;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipes->oldfd), -1);
	if (pid == 0)
	{
		if (here_fd && here_fd[pipes->i] != -1)
			dup2(here_fd[pipes->i], STDIN_FILENO);
		else
			dup2(pipes->oldfd, STDIN_FILENO);
		1 && (close(pipes->oldfd), cl_fd(here_fd, pipes->docs),
			free(here_fd), ext = do_redirections(split,
				skip_cmd(split, pipes->i), env, pipes),
			free_split(split), free_env(&env), exit (ext), 0);
	}
	close(pipes->oldfd);
	if (here_fd && here_fd[pipes->i] != -1)
		close(here_fd[pipes->i]);
	return (pid);
}

int	nb_of_docs(char **split)
{
	int	i;
	int	res;

	res = 0;
	i = -1;
	while (split[++i])
		if (!ft_strcmp(split[i], "<<"))
			res++;
	return (res);
}

int	do_pipe(char **split, t_env *env)
{
	int		pids[1024];
	int		*here_fd;
	t_pipes	*pipes;
	int		ext;

	pipe_norm(pids, &pipes, split);
	here_fd = here_prep(split, env, pipes);
	if (!here_fd && pipes->docs > 0)
		return (ext = pipes->err, free(pipes), ext);
	if (pipes->nb == 0)
		return (solo(split, env, here_fd, pipes));
	pids[pipes->i] = first(split, env, pipes, here_fd);
	if (pids[pipes->i] == -1)
		return (free(here_fd), free(pipes), 1);
	while (pipes->i < pipes->nb)
	{
		pids[pipes->i] = mid(split, env, pipes, here_fd);
		if (pids[pipes->i] == -1)
			return (free(here_fd), free(pipes), 1);
	}
	pids[pipes->i] = last(split, env, pipes, here_fd);
	if (pids[pipes->i] == -1)
		return (free(here_fd), free(pipes), 1);
	ext = child_code(pids, pipes->nb, pipes->i);
	return (cl_fd(here_fd, pipes->docs), free(here_fd), free(pipes), ext);
}
