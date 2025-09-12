/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:24 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/12 15:21:36 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_heredoc(char *file)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (strncmp(line, file, ft_strlen(file)) == 0
			&& line[ft_strlen(file)] == '\n')
		{
			free(line);
			break ;
		}
		write(STDIN_FILENO, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
	}
}
