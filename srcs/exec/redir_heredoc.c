/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/22 14:51:12 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

static void	heredoc_signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

static void	read_heredoc_lines(char *delimiter, int pipe_fd)
{
	char	*line;

	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
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

static void	handle_child_process(char *delimiter, int *pipe_fd, int infile,
			int outfile)
{
	close(pipe_fd[0]);
	read_heredoc_lines(delimiter, pipe_fd[1]);
	1 && (close(pipe_fd[1]), close(infile), close(outfile));
	exit(0);
}

static int	handle_parent_process(int *pipe_fd, pid_t pid,
			void *old_sigint_handler)
{
	int	status;

	1 && (close(pipe_fd[1]), waitpid(pid, &status, 0),
		signal(SIGINT, old_sigint_handler));
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipe_fd[0]), -1);
	return (pipe_fd[0]);
}

int	do_heredoc(char *delimiter, int infile, int outfile)
{
	int		pipe_fd[2];
	pid_t	pid;
	void	*old_sigint_handler;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	old_sigint_handler = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		signal(SIGINT, old_sigint_handler);
		1 && (perror("minishell: fork"), close(pipe_fd[0]), close(pipe_fd[1]));
		return (-1);
	}
	if (pid == 0)
		handle_child_process(delimiter, pipe_fd, infile, outfile);
	return (handle_parent_process(pipe_fd, pid, old_sigint_handler));
}
