/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:58:55 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/22 13:12:39 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_redirection_fds(int *infile, int *outfile)
{
	*infile = dup(STDIN_FILENO);
	if (*infile == -1)
		return (perror("minishell: "), -1);
	*outfile = dup(STDOUT_FILENO);
	if (*outfile == -1)
		return (close(*infile), perror("minishell: "), -1);
	return (0);
}

int	close_redir(int opens[2])
{
	if (dup2(opens[0], STDIN_FILENO) == -1)
		return (close(opens[0]), close(opens[1]), perror("minishell: "), -1);
	if (dup2(opens[1], STDOUT_FILENO) == -1)
		return (close(opens[0]), close(opens[1]), perror("minishell: "), -1);
	return (close(opens[0]), close(opens[1]), 0);
}

int	open_file(int red_type, char *file)
{
	int	fd;

	fd = -1;
	if (red_type == 3)
		fd = open(file, O_RDONLY);
	else if (red_type == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red_type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror("minishell: ");
	return (fd);
}

int	apply_redirection(int red_type, int fd)
{
	if (red_type == 1 || red_type == 2)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("minishell: "), -1);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("minishell: "), -1);
	}
	return (0);
}

int	shortcut(int opens[2], int *fd, char *file, int red_type)
{
	if (red_type == 4)
	{
		*fd = do_heredoc(file, opens[0], opens[1]);
		if (*fd == -1)
			return (close(opens[0]), close(opens[1]), -1);
		if (dup2(*fd, STDIN_FILENO) == -1)
			return (close(opens[0]), close(opens[1]),
				close(*fd), perror("minishell: "), -1);
		close(*fd);
	}
	else
	{
		*fd = open_file(red_type, file);
		if (*fd == -1)
			return (close(opens[0]), close(opens[1]), -1);
		if (apply_redirection(red_type, *fd) == -1)
			return (close(opens[0]), close(opens[1]), close(*fd), -1);
		close(*fd);
	}
	return (0);
}

int	open_redir(int red_type, char *file)
{
	int	opens[2];
	int	fd;

	if (red_type < 0 || setup_redirection_fds(&opens[0], &opens[1]) == -1)
		return (-1);
	if (shortcut(opens, &fd, file, red_type) == -1)
		return (-1);
	return (close_redir(opens));
}
