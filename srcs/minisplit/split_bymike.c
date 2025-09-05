/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bymike.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:48 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/05 16:03:52 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**mike_split(char *s, t_env *env, int j)
{
	int		i;
	int		len;
	char	**mike;

	len = count_words(s);
	if (len == 0)
		return (NULL);
	printf("%d\n", len);
	mike = ft_calloc(len + 1, sizeof(char *));
	if (!mike)
		return (NULL);
	i = -1;
	j += skip_spaces(s);
	while (++i < len)
	{
		mike[i] = write_word(env, s + j, 0);
		if (!mike[i])
			return (free_split(mike), NULL);
		j += skip_word(s + j);
	}
	mike[i] = NULL;
	return (NULL);
}
