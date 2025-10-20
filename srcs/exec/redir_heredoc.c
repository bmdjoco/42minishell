/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/20 12:59:22 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc_lines(char *delimiter, int pipe_fd)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

static void	handle_child_process(char **split, t_env *env, int *pipe_fd, char *delim)
{
	int	exit_code;

	close(pipe_fd[0]);
	exit_code  = read_heredoc_lines(delim, pipe_fd[1]);
	close(pipe_fd[1]);
	free_env(env);
	free_split(split);
	free(delim);
	exit(exit_code);
}

static int	handle_parent_process(int *pipe_fd, pid_t pid)
{
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}

int	do_heredoc(char **split, t_env *env, char *delim)
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
		handle_child_process(split, env, pipe_fd, delim);
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
