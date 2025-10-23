/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/23 12:12:57 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_delimiter(char *line, char *delimiter, int pipe_fd, int tty)
{
	if (!line)
	{
		write(tty, "\nminishell: warning: here-documentat line ", 42);
		write(tty, "1 delimited by end-of-file (wanted `EOF')\n", 42);
		return (1);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& line[ft_strlen(delimiter)] == '\n')
	{
		free(line);
		return (1);
	}
	write(pipe_fd, line, ft_strlen(line));
	free(line);
	return (0);
}

static int	read_heredoc_lines(char *delimiter, int pipe_fd)
{
	char	*line;
	int		tty;

	tty = open("/dev/tty", O_WRONLY);
	if (tty == -1)
		return (1);
	while (1)
	{
		if (g_received_signal == 130)
			return (close(tty), g_received_signal);
		write(tty, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (check_delimiter(line, delimiter, pipe_fd, tty))
			break ;
	}
	return (close(tty), 0);
}

void	child_process(t_doc *doc, int *pipe_fd)
{
	int	exit_code;

	close(pipe_fd[0]);
	exit_code = read_heredoc_lines(doc->delim, pipe_fd[1]);
	close(pipe_fd[1]);
	free_split(doc->cmd);
	free(doc->delim);
	free_env(doc->env_dup);
	free(doc);
	exit (exit_code);
}

static int	handle_parent_process(int *pipe_fd, pid_t pid, int *outfd)
{
	close(pipe_fd[1]);
	*outfd = pipe_fd[0];
	return (get_code(pid));
}

int	do_heredoc(t_doc *doc, int *herefd, int i, t_pipes *pipes)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid == -1)
	{
		1 && (perror("minishell: fork"), close(pipe_fd[0]), close(pipe_fd[1]));
		return (-1);
	}
	if (pid == 0)
	{
		free_split(doc->og_split);
		close_fds(herefd, i);
		free(pipes);
		free(herefd);
		child_process(doc, pipe_fd);
	}
	exit_code = handle_parent_process(pipe_fd, pid, &herefd[i]);
	return (exit_code);
}
