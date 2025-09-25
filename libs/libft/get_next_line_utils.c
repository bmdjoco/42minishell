/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:14 by milo              #+#    #+#             */
/*   Updated: 2025/07/10 11:59:09 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_stash(char *stash)
{
	if (!stash || !*stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	return (stash);
}

void	cleanup(char **stash)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		free(stash[i]);
		stash[i] = NULL;
		i++;
	}
}
