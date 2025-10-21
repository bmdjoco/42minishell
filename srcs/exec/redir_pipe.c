/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:40:10 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/21 19:01:21 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child_code(int pids[1024], int nb)
{
	int	i;
	int	exit_code;
	int	status;
	int	first_error;

	i = 0;
	exit_code = 0;
	first_error = 0;
	while (i <= nb)
	{
		waitpid(pids[i], &status, 0);
		process_child_status(status, &first_error, &exit_code, (i == nb));
		i++;
	}
	if (first_error != 0)
		exit_code = first_error;
	g_received_signal = exit_code;
	return (exit_code);
}

int	first(char **split, t_env *env, int *oldfd, int *here_fd)
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
			close(here_fd[0]);
		}
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit_code = do_redirections(split, env);
		free_env(env);
		free_split(split);
		exit(exit_code);
	}
	close(pipefd[1]);
	if (here_fd && here_fd[0] != -1)
		close(here_fd[0]);
	*oldfd = pipefd[0];
	return (pid);
}

int	mid(char **split, t_env *env, int *oldfd, int i, int *here_fd)
{
	pid_t	pid;
	int		prevfd;
	int		pipefd[2];
	int		exit_code;

	prevfd = *oldfd;
	if (pipe(pipefd) == -1)
		return (perror("minishell: "), close(prevfd), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipefd[0]),
			close(pipefd[1]), close(prevfd), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (here_fd && here_fd[i] != -1)
		{
			dup2(here_fd[i], STDIN_FILENO);
			close(here_fd[i]);
		}
		else
			dup2(prevfd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(prevfd);
		exit_code = do_redirections(split + skip_cmd(split, i), env);
		free_env(env);
		free_split(split);
		exit(exit_code);
	}
	close(prevfd);
	close(pipefd[1]);
	if (here_fd && here_fd[i] != -1)
		close(here_fd[i]);
	*oldfd = pipefd[0];
	return (pid);
}

int	last(char **split, t_env *env, int oldfd, int i, int *here_fd)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(oldfd), -1);
	if (pid == 0)
	{
		if (here_fd && here_fd[i] != -1)
		{
			dup2(here_fd[i], STDIN_FILENO);
			close(here_fd[i]);
		}
		else
			dup2(oldfd, STDIN_FILENO);
		close(oldfd);
		exit_code = do_redirections(split + skip_cmd(split, i), env);
		free_env(env);
		free_split(split);
		exit(exit_code);
	}
	close(oldfd);
	if (here_fd && here_fd[i] != -1)
		close(here_fd[i]);
	return (pid);
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
			exit_code = do_redirections(split, env);
			free_env(env);
			free_split(split);
			exit (exit_code);
		}
		close(herefd[0]);
		return (get_code(pid));
	}
	return (do_redirections(split, env));
}

int	do_pipe(char **split, t_env *env)
{
	int	i;
	int	pids[1024];
	int	nb;
	int	oldfd;
	int	*here_fd;

	i = 0;
	nb = nb_of_pipe(split);
	here_fd = here_prep(split, env, nb + 1);
	if (!here_fd)
		return (g_received_signal);
	if (nb == 0)
	{
		i = solo(split, env, here_fd);
		return (free(here_fd), i);
	}
	pids[i] = first(split, env, &oldfd, here_fd);
	if (pids[i] == -1)
		return (free(here_fd), 1);
	i++;
	while (i < nb)
	{
		pids[i] = mid(split, env, &oldfd, i, here_fd);
		if (pids[i] == -1)
			return (free(here_fd), 1);
		i++;
	}
	pids[i] = last(split, env, oldfd, i, here_fd);
	if (pids[i] == -1)
		return (free(here_fd), 1);
	free(here_fd);
	return (child_code(pids, nb));
}
