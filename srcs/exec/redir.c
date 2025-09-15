/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:58:55 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/15 15:02:34 by miltavar         ###   ########.fr       */
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

int	close_redir(int infile, int outfile)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		return (close(infile), close(outfile), perror("minishell: "), -1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(infile), close(outfile), perror("minishell: "), -1);
	return (close(infile), close(outfile), 0);
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

int	open_redir(int red_type, char *file)
{
	int	infile;
	int	outfile;
	int	fd;

	if (red_type < 0 || setup_redirection_fds(&infile, &outfile) == -1)
		return (-1);
	if (red_type == 4)
	{
		fd = do_heredoc(file, infile, outfile);
		if (fd == -1)
			return (close(infile), close(outfile), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(infile), close(outfile),
				close(fd), perror("minishell: "), -1);
	}
	else
	{
		fd = open_file(red_type, file);
		if (fd == -1)
			return (close(infile), close(outfile), -1);
		if (apply_redirection(red_type, fd) == -1)
			return (close(infile), close(outfile), close(fd), -1);
	}
	close(fd);
	return (close_redir(infile, outfile));
}
