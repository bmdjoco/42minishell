/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:00:46 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/12 14:21:49 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_operators(char *s, int i)
{
	while (s[i] && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
		i++;
	return (i);
}

int	skip_single_quotes(char *s, int i)
{
	i++;
	while (s[i] && s[i] != '\'')
		i++;
	if (s[i] == '\'')
		i++;
	return (i);
}

int	skip_env_var(char *s, int i)
{
	i++;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

int	skip_double_quotes(char *s, int i)
{
	i++;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$')
			i = skip_env_var(s, i);
		else
			i++;
	}
	if (s[i] == '"')
		i++;
	return (i);
}

int	skip_unquoted_content(char *s, int i)
{
	while (s[i] && s[i] != '\'' && s[i] != '"' && s[i] != '>'
		&& s[i] != '<' && s[i] != '|' && !is_whitespace(s[i]))
	{
		if (s[i] == '$')
			i = skip_env_var(s, i);
		else
			i++;
	}
	return (i);
}
