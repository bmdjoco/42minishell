/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:58:55 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/09 14:52:41 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_redirections(char **split, t_env *env)
{
	int		i;
	int		tmp;
	int		redir;
	char	*file;

	i = -1;
	redir = nb_of_redir(split);
	if (redir > 0)
		while (++i < redir)
		{
			file = reddir_file(split, i);
			if (!file)
				return (-1);
			tmp = exec_redir(split, reddir_type(split, i), file, env);
			if (tmp == -1)
				return (-1);
			free(file);
		}
	else
		parse_line(split, env);
	return (1);
}

int	open_file(int red_type, char *file)
{
	int	fd;

	if (red_type == 4);
		//here_doc;
	else if (red_type == 3)
		fd = open(file, O_RDONLY);
	else if (red_type == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red_type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	exec_redir(char **split, int red_type, char *file, t_env *env)
{
	int	infile;
	int	outfile;
	int	fd;

	infile = dup(STDIN_FILENO);
	if (infile == -1)
		return (-1);
	outfile = dup(STDOUT_FILENO);
	if (outfile == -1)
		return (close(infile), -1);
	fd = open_file(red_type, file);
	if (fd == -1)
		return (close(infile), close(outfile), -1);
	if (red_type == 1 || red_type == 2)
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(infile), close(outfile), close(fd), -1);
	else
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(infile), close(outfile), close(fd), -1);
	parse_line(split, env);
	if (dup2(infile, STDIN_FILENO) == -1)
		return (close(infile), close(outfile), close(fd), -1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(infile), close(outfile), close(fd), -1);
	return (close(infile), close(outfile), close(fd), 1);
}
