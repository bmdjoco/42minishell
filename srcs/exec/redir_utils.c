/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:04 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/15 15:03:41 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief renvoie le nombre de redirection de la commande
 */
int	nb_of_redir(char **split)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (split[i] && split[i][0] != '|')
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			res++;
		i++;
	}
	return (res);
}

/**
 * @brief renvoie le type de redirection a faire a la red position
 *
 * @return 1 pour >>, 2 pour >, 3 pour <, 4 pour <<
 * @return -1 en cas d'erreur
 */
int	reddir_type(char **split, int red)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red)
		{
			if (!ft_strcmp(">>", split[i]))
				return (1);
			else if (!ft_strcmp(">", split[i]))
				return (2);
			else if (!ft_strcmp("<", split[i]))
				return (3);
			else if (!ft_strcmp("<<", split[i]))
				return (4);
		}
		i++;
	}
	return (-1);
}

/**
 * @brief renvoie le nom de redirection a faire a la red position
 *
 * @return le nom du fichier de redirection
 */
char	*reddir_file(char **split, int red)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red && split[i + 1])
			return (ft_strdup(split[i + 1]));
		i++;
	}
	return (NULL);
}

int	exec_redir(char **split, int red_type, char *file, t_env *env)
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
	return (distributor(split, env), close_redir(infile, outfile));
}

/**
 * @brief gere les redirections, open et distribue a parse_line
 * @param split ensemble de chaines des arguments de commande
 * @param env ensemble des variables environnementales
 * @return 1 en cas de succes, -1 en cas d'erreur
 */
int	do_redirections(char **split, t_env *env, int i)
{
	int		tmp;
	int		redir;
	char	*file;

	redir = nb_of_redir(split);
	if (redir > 0)
	{
		while (++i < redir)
		{
			file = reddir_file(split, i + 1);
			if (!file)
				return (perror("minishell: "), -1);
			if (i == redir - 1)
				tmp = exec_redir(split, reddir_type(split, i + 1), file, env);
			else
				tmp = open_redir(reddir_type(split, i + 1), file);
			if (tmp == -1)
				return (free(file), perror("minishell: "), -1);
			free(file);
		}
	}
	else
		distributor(split, env);
	return (1);
}
