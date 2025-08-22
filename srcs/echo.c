/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:46:13 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 12:45:07 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(char *s)
{
	int	i;

	i = strstr_index(s, "echo -n");
	if (i > 0)
	{
		redirection_check(s + i);
		return (1);
	}
	else
	{
		i = strstr_index(s, "echo");
		if (i > 0)
		{
			redirection_check(s + i);
			return (1);
		}
	}
	return (-1);
}

int	redirection_check(char *s)
{
	int	i;
	char	*eof;

	i = strstr_index(s, "<<");
	if (i > 0)
	{
		eof = malloc(ft_strlen(s + i));
		if (!eof)
			return (perror("minishell: alloc failed\n"), -1);
		ft_strlcpy(eof, s + i, )
		echo_doc()
	}
}

char	*parse_eof(char *s)
{
	char	*eof;
	int			i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	i = ft_strlen(s) - i;
	eof = malloc(i + 1);
	if (!eof)
}
