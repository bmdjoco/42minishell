/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:14:38 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/03 11:14:44 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**get_args(char *s)
{
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	res = ft_calloc(4, 8);
	if (!res)
		return (NULL);
	while (s[i] && ft_isalpha(s[i]))
		i++;
	res[0] = ft_strndup(s, i);
	if (!res[0])
		return (free(res), NULL);
	res[1] = ft_strndup(s + i, 1);
	if (!res[1])
		return (free(res[0]), free(res), NULL);
	i++;
	res[2] = ft_strndup(s + i, ft_strlen(s + i));
	if (!res[2])
		return (free(res[1]), free(res[0]), free(res), NULL);
	res[3] = NULL;
	return (res);
}
