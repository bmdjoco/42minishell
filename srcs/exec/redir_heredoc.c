/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/16 14:03:20 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	read_heredoc_lines(char *delimiter, int pipe_fd)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_received_signal == 130)
		{
			if (line)
				free(line);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		free(line);
	}
}

static void	handle_child_process(t_redir_util *util, int *pipe_fd)
{
	close(pipe_fd[0]);
	read_heredoc_lines(util->file, pipe_fd[1]);
	dup2(util->original[0], STDIN_FILENO);
	dup2(util->original[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	close(util->original[0]);
	close(util->original[1]);
	if (util->env)
		free_env(util->env);
	if (util->og_split)
		free_split(util->og_split);
	if (util->file)
		free(util->file);
	if (util)
		free(util);
	exit(0);
}

static int	handle_parent_process(int *pipe_fd, pid_t pid)
{
	int	status;

	1 && (close(pipe_fd[1]), waitpid(pid, &status, 0));
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipe_fd[0]), -1);
	return (pipe_fd[0]);
}

int	do_heredoc(t_redir_util *util)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid == -1)
	{
		1 && (perror("minishell: fork"), close(pipe_fd[0]), close(pipe_fd[1]));
		return (-1);
	}
	if (pid == 0)
		handle_child_process(util, pipe_fd);
	return (handle_parent_process(pipe_fd, pid));
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
