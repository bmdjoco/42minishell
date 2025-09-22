/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:04 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/22 15:24:48 by miltavar         ###   ########.fr       */
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
	char	*res;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red && split[i + 1])
		{
			res = ft_strdup(split[i + 1]);
			if (!res)
				return (NULL);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	exec_redir(char **split, int red_type, char *file, t_env *env)
{
	int		opens[2];
	int		fd;
	int		result;
	char	**nw_split;

	if (red_type < 0 || setup_redirection_fds(&opens[0], &opens[1]) == -1)
		return (-1);
	if (shortcut(opens, &fd, file, red_type) == -1)
		return (-1);
	nw_split = split_again(split);
	if (nw_split)
	{
		parse_line(nw_split, env);
		free_split(nw_split);
	}
	result = close_redir(opens);
	return (result);
}

/**
 * @brief gere les redirections, open et distribue a parse_line
 * @param split ensemble de chaines des arguments de commande
 * @param env ensemble des variables environnementales
 * @return 1 en cas de succes, -1 en cas d'erreur
 */
int	do_redirections(char **split, t_env *env)
{
	int		redir;
	int		original_stdin;
	int		original_stdout;

	redir = nb_of_redir(split);
	if (redir <= 0)
		return (distributor(split, env), 1);
	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
		return (perror("minishell: dup"), -1);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
		return (close(original_stdin), perror("minishell: dup"), -1);
	if (process_all_redirections(split, redir, original_stdin, original_stdout) == -1)
		return (close(original_stdin), close(original_stdout), -1);
	execute_with_redirections(split, env);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (1);
}
