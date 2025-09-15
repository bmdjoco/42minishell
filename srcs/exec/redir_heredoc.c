/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/15 14:43:37 by miltavar         ###   ########.fr       */
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
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& line[ft_strlen(delimiter)] == '\n'))
		{
			if (line)
				free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		free(line);
	}
}

int	do_heredoc(char *delimiter, int infile, int outfile)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), close(pipe_fd[0]),
			close(pipe_fd[1]), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		read_heredoc_lines(delimiter, pipe_fd[1]);
		close(pipe_fd[1]);
		close(infile);
		close(outfile);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}
