/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:49:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/05 12:02:58 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	detect_next(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (-1);
	if (!is_whitespace(s[i]))
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
	else if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
		i++;
	else if (s[i] == '>' && s[i + 1] && s[i + 1] != '>')
		i++;
	else if (s[i] == '|' && s[i + 1] && s[i + 1] != '|')
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

int	match_quotes(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
		if (s[i] == '"')
			i++;
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
		if (line[i] == '"' || line[i] == '\'')
		{
			if (match_quotes(line + i) == -1)
				return (ft_fprintf(1, "here 1\n"), -1);
			else
				i += match_quotes(line + i);
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			len = check_next(line + i);
			if (len == -1)
				return (ft_fprintf(1, "here 2\n"),-1);
			else
				i += len;
		}
		else
			i++;
	}
	return (0);
}
