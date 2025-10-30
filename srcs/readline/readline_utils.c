/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:49:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/30 13:46:29 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "minishell.h"

int	match_quotes(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		char c = s[i];
		i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] == c)
			return (i + 1);
	}
	return (-1);
}

static int	is_it_good(char *s, int i)
{
	while (s[i] && is_whitespace(s[i]))
		i++;
	if (!s[i])
		return (-1);
	if (s[i] == '<' || s[i] == '>')
		return (-1);
	return (1);
}

static int	check_redir(char *s, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
		*i += 2;
	else if (s[*i] == '>' && s[*i + 1] == '>')
		*i += 2;
	else
		(*i)++;
	if (is_it_good(s, *i) == -1)
		return (-1);
	return (0);
}

static int	check_pipe(char *s, int *i)
{
	if (s[*i + 1] == '|')
		return (-1);
	(*i)++;
	while (s[*i] && is_whitespace(s[*i]))
		(*i)++;
	if (!s[*i])
		return (-1);
	if (s[*i] == '|')
		return (-1);
	return (0);
}

int	check_syntax_err(char *line, int i, int len)
{
	if (line[0] == '|')
		return (syntax_msg(line[0]), -1);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			len = match_quotes(line + i);
			if (len == -1)
				return (syntax_msg(line[i]), -1);
			i += len;
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			if (check_redir(line, &i) == -1)
				return (syntax_msg(line[i]), -1);
		}
		else if (line[i] == '|')
		{
			if (check_pipe(line, &i) == -1)
				return (syntax_msg(line[i]), -1);
		}
		else
			i++;
	}
	return (0);
}


int	check_limit(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (1);
	else if (!ft_strcmp(s, "<"))
		return (1);
	else if (!ft_strcmp(s, "<<"))
		return (1);
	else if (!ft_strcmp(s, ">>"))
		return (1);
	else if (!ft_strcmp(s, "|"))
		return (1);
	return (0);
}
