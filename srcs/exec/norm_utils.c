/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:10:56 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/26 14:37:30 by miltavar         ###   ########.fr       */
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

int	pipe_fork(int *pipefd, pid_t *pid)
{
	if (pipe(pipefd) == -1)
		return (-1);
	*pid = fork();
	if (*pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	return (0);
}
