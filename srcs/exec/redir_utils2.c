/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:30:00 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/22 15:32:49 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Applique une redirection heredoc
 */
static int	apply_heredoc_redir(char *file, int orig_in, int orig_out)
{
	int	fd;

	fd = do_heredoc(file, orig_in, orig_out);
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
static int	apply_normal_redir(int red_type, char *file)
{
	int	fd;

	fd = open_file(red_type, file);
	if (fd == -1)
		return (-1);
	if (apply_redirection(red_type, fd) == -1)
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
int	apply_single_redirect(int red_type, char *file, int orig_in, int orig_out)
{
	if (red_type == 4)
		return (apply_heredoc_redir(file, orig_in, orig_out));
	else
		return (apply_normal_redir(red_type, file));
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
int	process_all_redirections(char **split, int redir, int orig_in, int orig_out)
{
	char	*file;
	int		red_type;
	int			i;

	i = -1;
	while (++i < redir)
	{
		file = reddir_file(split, i + 1);
		if (!file)
			return (perror("minishell: "), -1);
		red_type = reddir_type(split, i + 1);
		if (apply_single_redirect(red_type, file, orig_in, orig_out) == -1)
			return (free(file), perror("minishell: "), -1);
		free(file);
	}
	return (0);
}
