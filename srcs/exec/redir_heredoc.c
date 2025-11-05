/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/05 14:44:51 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_delimiter(char *line, t_doc *doc, int pipe_fd)
{
	char	*expand;

	if (!line)
	{
		ft_fprintf(2, "\nminishell: warning: here-documentat line 1 del");
		ft_fprintf(2, "imited by end-of-file (wanted `%s')\n", doc->delim);
		return (1);
	}
	if (ft_strncmp(line, doc->delim, ft_strlen(doc->delim)) == 0
		&& line[ft_strlen(doc->delim)] == '\n')
	{
		free(line);
		return (1);
	}
	expand = expand_doc(line, doc->env_dup);
	if (!expand)
		expand = line;
	free(line);
	write(pipe_fd, expand, ft_strlen(expand));
	free(expand);
	return (0);
}

static int	read_heredoc_lines(t_doc *doc, int pipe_fd)
{
	char	*line;

	while (1)
	{
		if (g_received_signal == 130)
			return (130);
		write(2, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (check_delimiter(line, doc, pipe_fd))
			break ;
	}
	return (0);
}

void	child_process(t_doc *doc, int *pipe_fd)
{
	int	exit_code;

	close(pipe_fd[0]);
	exit_code = read_heredoc_lines(doc, pipe_fd[1]);
	close(pipe_fd[1]);
	free(doc->delim);
	free_env(&doc->env_dup);
	free(doc);
	exit (exit_code);
}

static int	handle_parent_process(int *pipe_fd, pid_t pid, int *outfd)
{
	close(pipe_fd[1]);
	*outfd = pipe_fd[0];
	return (get_code(pid));
}

int	do_heredoc(t_doc *doc, int *herefd, t_pipes *pipes)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), close(pipe_fd[0]), close(pipe_fd[1]));
	if (pid == 0)
	{
		1 && (doc_distributor(), free_split(doc->og_split), 0);
		if (herefd)
			cl_fd(herefd, doc->i - 1);
		free(pipes);
		free(herefd);
		child_process(doc, pipe_fd);
	}
	doc_ignore();
	exit_code = handle_parent_process(pipe_fd, pid, &herefd[doc->i]);
	signal_distributor();
	return (exit_code);
}
