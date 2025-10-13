/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:40:10 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/13 15:40:16 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_cmd(char **split, int i)
{
	int	j;
	int	pipes;

	j = -1;
	pipes = 0;
	while (split[++j])
	{
		if (!ft_strcmp(split[j], "|"))
			pipes++;
		if (pipes == i && split[j + 1])
			return (j + 1);
	}
	return (93);
}

int	first(char **split, t_env *env, int *oldfd)
{
	int	exit_code;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		return (1);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit_code = do_redirections(split, env);
	*oldfd = pipefd[0];
	return (exit_code);
}

int	mid(char **split, t_env *env, int *oldfd, int i)
{
	int	exit_code;
	int	prevfd;
	int	pipefd[2];

	prevfd = *oldfd;
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		return (1);
	}
	dup2(prevfd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(prevfd);
	close(pipefd[1]);
	exit_code = do_redirections(split + skip_cmd(split, i), env);
	*oldfd = pipefd[0];
	return (exit_code);
}

int	last(char **split, t_env *env, int oldfd, int i)
{
	dup2(oldfd, STDIN_FILENO);
	close(oldfd);
	return (do_redirections(split + skip_cmd(split, i), env));
}

int	do_pipe(char **split, t_env *env)
{
	int	i;
	int	nb;
	int	oldfd;
	int	exit_code;

	i = -1;
	nb = nb_of_pipe(split);
	if (nb == 0)
		return (do_redirections(split, env));
	exit_code = first(split, env, &oldfd);
	if (exit_code != 0)
		return (close(oldfd), exit_code);
	i++;
	while (++i < nb - 1)
	{
		exit_code = mid(split, env, &oldfd, i);
		if (exit_code != 0)
			return (close(oldfd), exit_code);
	}
	exit_code = last(split, env, oldfd, i);
	if (exit_code != 0)
		return (close(oldfd), exit_code);
	return (0);
}
