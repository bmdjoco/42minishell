/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:25:00 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 12:32:22 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	strstr_index(char *s, char *tofind) //ft_strstr to find qui return l'index
{
	int	i;
	int	j;

	if (!s || !tofind)
		return (-1);
	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == tofind[j])
		{
			while (s[i + j] == tofind[j])
			{
				j++;
			}
			if (!tofind[j] && s[i + j + 1] && s[i + j + 1] == ' ')
				return (j + 1);
		}
		i++;
	}
	return (-1);
}

void	echo_doc(char *end) // here_doc pour echo simple
{
	char	*line;

	write(STDOUT_FILENO, "heredoc> ", 9);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (strncmp(line, end, ft_strlen(end)) == 0
			&& line[ft_strlen(end)] == '\n')
		{
			free(line);
			break ;
		}
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "heredoc> ", 9);
	}
	exit(1);
}
