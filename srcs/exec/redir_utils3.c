/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:52:43 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/22 14:52:55 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redir(int red_type, char *file)
{
	int	opens[2];
	int	fd;

	if (red_type < 0 || setup_redirection_fds(&opens[0], &opens[1]) == -1)
		return (-1);
	if (shortcut(opens, &fd, file, red_type) == -1)
		return (-1);
	return (close_redir(opens));
}
