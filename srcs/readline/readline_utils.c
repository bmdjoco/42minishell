/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:49:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/11 13:58:06 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	match_quotes(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
		if (s[i] == '"')
			return (i + 1);
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		if (s[i] == '\'')
			return (i + 1);
	}
	return (-1);
}

int	is_it_good(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (-1);
	while (s[i] && is_whitespace(s[i]))
		i++;
	if (!s[i])
		return (-1);
	if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		return (-1);
	return (1);
}

int	check_next(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '>' && !s[i + 1])
		return (-1);
	else if (s[i] == '<' && !s[i + 1])
		return (-1);
	else if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
		i++;
	else if (s[i] == '>' && s[i + 1] && s[i + 1] != '>')
		i++;
	else if (s[i] == '|' && !s[i + 1])
		return (-1);
	else if (s[i] == '|' && s[i + 1] && s[i + 1] != '|')
		i++;
	else if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
		i = i + 2;
	else if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
		i = i + 2;
	if (i <= 0)
		return (-1);
	if (is_it_good(s + i) == -1)
		return (-1);
	return (1);
}

int	check_syntax_err(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			len = match_quotes(line + i);
			if (len == -1)
				return (ft_fprintf(2, "minishell: syntax error near unexpected token '%c'\n", line[i]), -1);
			i += len;
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			len = check_next(line + i);
			if (len == -1)
				return (ft_fprintf(2, "minishell: syntax error near unexpected token '%c'\n", line[i]), -1);
			i += len;
		}
		else
			i++;
	}
	return (0);
}

int	distributor(char **split, t_env *env)
{
	char	**nw_split;
	int		return_code;

	return_code = 0;
	nw_split = split_again(split);
	if (!nw_split)
		return (-1);
	return_code = (parse_line(nw_split, env));
	free_split(nw_split);
	return (return_code);
}
