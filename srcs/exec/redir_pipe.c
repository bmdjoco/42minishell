/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:40:10 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/25 15:25:03 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child_code(int pids[1024], int nb, int i)
{
	int	exit_code;
	int	status;

	i = 0;
	exit_code = 0;
	while (i <= nb)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		else
			exit_code = 1;
		i++;
	}
	g_received_signal = exit_code;
	return (exit_code);
}

int	first(char **split, t_env *env, t_pipes *pipes, int *here_fd)
{
	pid_t	pid;
	int		pipefd[2];
	int		exit_code;

	if (pipe(pipefd) == -1)
		return (perror("minishell: "), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipefd[0]), close(pipefd[1]), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (here_fd && here_fd[0] != -1)
		{
			dup2(here_fd[0], STDIN_FILENO);
			close_fds(here_fd, pipes->nb + 1);
		}
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close_fds(here_fd, pipes->nb + 1);
		free(here_fd);
		exit_code = do_redirections(split, 0, env, pipes);
		free_split(split);
		free_env(env);
		exit(exit_code);
	}
	close(pipefd[1]);
	if (here_fd && here_fd[0] != -1)
		close(here_fd[0]);
	pipes->oldfd = pipefd[0];
	return (pid);
}

int	mid(char **split, t_env *env, t_pipes *pipes, int *here_fd)
{
	pid_t	pid;
	int		prevfd;
	int		pipefd[2];
	int		exit_code;

	prevfd = pipes->oldfd;
	if (pipe(pipefd) == -1)
		return (perror("minishell: "), close(prevfd), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipefd[0]),
			close(pipefd[1]), close(prevfd), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (here_fd && here_fd[pipes->i] != -1)
		{
			dup2(here_fd[pipes->i], STDIN_FILENO);
			close_fds(here_fd, pipes->nb + 1);
		}
		else
			dup2(prevfd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(prevfd);
		close_fds(here_fd, pipes->nb + 1);
		free(here_fd);
		exit_code = do_redirections(split,
				skip_cmd(split, pipes->i), env, pipes);
		free_split(split);
		free_env(env);
		exit(exit_code);
	}
	close(prevfd);
	close(pipefd[1]);
	if (here_fd && here_fd[pipes->i] != -1)
		close(here_fd[pipes->i]);
	pipes->oldfd = pipefd[0];
	return (pid);
}

int	last(char **split, t_env *env, t_pipes *pipes, int *here_fd)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipes->oldfd), -1);
	if (pid == 0)
	{
		if (here_fd && here_fd[pipes->i] != -1)
		{
			dup2(here_fd[pipes->i], STDIN_FILENO);
			close_fds(here_fd, pipes->nb + 1);
		}
		else
			dup2(pipes->oldfd, STDIN_FILENO);
		close(pipes->oldfd);
		close_fds(here_fd, pipes->nb + 1);
		free(here_fd);
		exit_code = do_redirections(split,
				skip_cmd(split, pipes->i), env, pipes);
		free_split(split);
		free_env(env);
		exit(exit_code);
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
	int		exit_code;

	pipes = malloc(sizeof(t_pipes));
	if (!pipes)
		return (perror("minishell: "), 1);
	pipes->i = 0;
	pipes->docs = nb_of_docs(split);
	pipes->nb = nb_of_pipe(split);
	here_fd = here_prep(split, env, pipes->docs, pipes);
	if (!here_fd)
		return (free(pipes), g_received_signal);
	if (pipes->nb == 0)
	{
		exit_code = solo(split, env, here_fd, pipes);
		return (exit_code);
	}
	pids[pipes->i] = first(split, env, pipes, here_fd);
	if (pids[pipes->i] == -1)
		return (free(here_fd), free(pipes), 1);
	pipes->i++;
	while (pipes->i < pipes->nb)
	{
		pids[pipes->i] = mid(split, env, pipes, here_fd);
		if (pids[pipes->i] == -1)
			return (free(here_fd), free(pipes), 1);
		pipes->i++;
	}
	pids[pipes->i] = last(split, env, pipes, here_fd);
	if (pids[pipes->i] == -1)
		return (free(here_fd), free(pipes), 1);
	exit_code = child_code(pids, pipes->nb, pipes->i);
	return (free(here_fd), free(pipes), exit_code);
}
