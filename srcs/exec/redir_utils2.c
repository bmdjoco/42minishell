/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:30:00 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/23 15:11:11 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Applique une redirection heredoc
 */
static int	apply_heredoc_redir(t_redir_util *util)
{
	util->fd = do_heredoc(util);
	if (util->fd == -1)
		return (-1);
	if (dup2(util->fd, STDIN_FILENO) == -1)
	{
		close(util->fd);
		return (-1);
	}
	close(util->fd);
	return (0);
}

/**
 * @brief Applique une redirection normale (>, <, >>)
 */
static int	apply_normal_redir(t_redir_util *util)
{
	util->fd = open_file(util->red_type, util->file);
	if (util->fd == -1)
		return (-1);
	if (apply_redirection(util->red_type, util->fd) == -1)
	{
		close(util->fd);
		return (-1);
	}
	close(util->fd);
	return (0);
}

/**
 * @brief Applique une seule redirection selon son type
 */
int	apply_single_redirect(t_redir_util *util)
{
	if (util->red_type == 4)
		return (apply_heredoc_redir(util));
	else
		return (apply_normal_redir(util));
}

/**
 * @brief Execute la commande avec les redirections actives
 */
int	execute_with_redirections(char **split, t_env *env)
{
	char	**nw_split;
	int		cmd_result;

	nw_split = split_again(split);
	if (nw_split)
	{
		cmd_result = parse_line(nw_split, env);
		(void)cmd_result;
		free_split(nw_split);
	}
	return (0);
}

/**
 * @brief Traite toutes les redirections dans la boucle principale
 */
int	process_all_redirections(t_redir_util *util)
{
	int		i;

	i = -1;
	while (++i < util->redir)
	{
		util->file = reddir_file(util->og_split, i + 1);
		if (!util->file)
			return (perror("minishell: "), -1);
		util->red_type = reddir_type(util->og_split, i + 1);
		if (apply_single_redirect(util) == -1)
			return (free(util->file), perror("minishell: "), -1);
		free(util->file);
	}
	return (0);
}
