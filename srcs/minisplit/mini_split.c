/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:48 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/09 12:46:41 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**mini_split(char *s, t_env *env)
{
	int		i;
	int		j;
	int		len;
	char	**split;

	len = count_words(s);
	if (len == 0)
		return (NULL);
	split = ft_calloc(len + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	j = 0;
	j += skip_spaces(s);
	while (++i < len)
	{
		split[i] = write_word(env, s + j, 0);
		if (!split[i])
			return (free_split(split), NULL);
		j += skip_word(s + j);
		j += skip_spaces(s + j);
	}
	split[i] = NULL;
	return (split);
}
