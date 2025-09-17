/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:18:26 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/17 15:18:35 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
