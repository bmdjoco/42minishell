/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:30:00 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/25 18:53:19 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		return (close(fd), -1);
	close(fd);
	return (0);
}

/**
 * @brief Applique une seule redirection selon son type
 */
int	apply_single_redirect(char *delim, int type)
{
	if (type == 4)
		return (0);
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
int	process_all_redirections(int nb, char **split)
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
		if (apply_single_redirect(delim, type) == -1)
			return (free(delim), -1);
		free(delim);
	}
	return (0);
}

int	go_to_cmd(int i, char **split)
{
	int j;

	j = 0;
	while (split[i + j][0] == '>' || split[i + j][0] == '<')
		j += 2;
	return (j);
}
