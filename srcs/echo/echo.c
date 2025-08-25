/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:46:13 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/25 15:55:13 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		eof = parse_eof(s + i);
		if (!eof)
			return (-1);
		echo_doc(eof);
	}
}

char	*parse_eof(char *s)
{
	char	*eof;
	int			i;
	int			j;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	eof = malloc((ft_strlen(s) - i + 1));
	if (!eof)
		return (perror("minishell: alloc failed\n"), NULL);
	j = 0;
	while (j < i)
	{
		eof[j] = s[j];
		j++;
	}
	eof[j] = '\0';
	return (eof);
}
