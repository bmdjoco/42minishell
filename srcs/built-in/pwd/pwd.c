/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:12:15 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/03 12:38:55 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief affiche le chemin actuellent utilise par le terminal
 */
void	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return ;
	printf("%s\n", path);
	free(path);
}
