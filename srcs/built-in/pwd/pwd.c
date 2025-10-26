/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:12:15 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/26 13:58:15 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief affiche le chemin actuellent utilise par le terminal
 */
int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_putstr_fd("minishell: pwd: error retrieving "
				"current directory\n",
				2), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}
