/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:30:00 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/20 13:50:18 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Applique une redirection heredoc
 */
static int	apply_heredoc_redir(char **split, t_env *env, char *delim)
{
	int	fd;

	fd = do_heredoc(split, env, delim);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Applique une redirection normale (>, <, >>)
 */
static int	apply_normal_redir(int type, char *delim)
{
	int	fd;

	fd = open_file(type, delim);
	if (fd == -1)
		return (-1);
	if (apply_redirection(type, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Applique une seule redirection selon son type
 */
int	apply_single_redirect(char **split, t_env *env, char *delim, int type)
{
	if (type == 4)
		return (apply_heredoc_redir(split, env, delim));
	else
		return (apply_normal_redir(type, delim));
}

/**
 * @brief Execute la commande avec les redirections actives
 */
int	execute_with_redirections(char **split, t_env *env)
{
	char	**nw_split;
	int		cmd_result;

	cmd_result = 0;
	nw_split = split_again(split);
	if (!nw_split)
		return (1);
	cmd_result = parse_line(nw_split, env);
	free_split(nw_split);
	return (cmd_result);
}

/**
 * @brief Traite toutes les redirections dans la boucle principale
 */
int	process_all_redirections(int nb, char **split, t_env *env)
{
	int		i;
	int		type;
	char	*delim;

	i = -1;
	while (++i < nb)
	{
		delim = reddir_file(split, i + 1);
		if (!delim)
			return (perror("minishell: "), -1);
		type = reddir_type(split, i + 1);
		if (apply_single_redirect(split, env, delim, type) == -1)
			return (free(delim), perror("minishell: "), -1);
		free(delim);
	}
	return (0);
}
