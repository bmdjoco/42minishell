/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:35:56 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/09 12:19:52 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_in_single(char *s, int *i)
{
	int	j;

	(*i)++;
	j = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] == '\'')
		(*i)++;
	return (*i - (j + 1));
}

void	go_end(char *s, int *i)
{
	while (s[*i])
		(*i)++;
}
int	skip_envkey(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

int	word_cond(char c)
{
	if (c && c != '|' && c != '>' && c != '<' && !is_whitespace(c))
		return (0);
	return (1);
}

int	skip_spaces(char *s)
{
	int	v;

	v = 0;
	while (s[v] && is_whitespace(s[v]))
		v++;
	return (v);
}
