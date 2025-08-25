/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:35:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/25 17:13:14 by miltavar         ###   ########.fr       */
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
