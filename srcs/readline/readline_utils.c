/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:49:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/09 16:11:25 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	detect_next(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (-1);
	while (is_whitespace(s[i]))
		i++;
	if (!s[i])
		return (-1);
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		return (-1);
	return (0);
}

static int	check_next(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (-1);
	if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
		i = i + 2;
	else if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
		i = i + 2;
	else if (s[i] == '<' && s[i + 1])
		i++;
	else if (s[i] == '>' && s[i + 1])
		i++;
	else if (s[i] == '|')
		i++;
	if (i > 0)
	{
		if (detect_next(s + i) == -1)
			return (-1);
		else
			return (i);
	}
	return (-1);
}

int	match_quotes(char *s, int *i)
{
	if (!s)
		return (0);
	*i = 0;
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '"')
			(*i)++;
		if (s[*i] == '"')
			(*i)++;
		return (i);
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		if (s[i] == '\'')
			i++;
		return (i);
	}
	return (-1);
}

int	check_syntax_err(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')

	}
	return (0);
}
