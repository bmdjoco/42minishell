/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:35:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/26 14:59:06 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (i);
}

int	single(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] && s[i] == '\'')
				i++;
			else
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	doubles(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] && s[i] == '"')
				i++;
			else
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	check_quotes(char *s)
{
	int	i;

	i = single(s);
	if (i == -1)
		return (-1);
	i = doubles(s);
	if (i == -1)
		return (-1);
	return (0);
}
