/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:33:14 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/25 19:50:40 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @return Renvoie le nombre de repertoire prent d'un path
 *
 * @param path chemin d'acces debutant par un /
 */
int	nb_parent(char	*path)
{
	int		nb;
	int		i;

	nb = 0;
	i = 1;
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			i++;
		if (path[i])
			i++;
		nb++;
	}
	return (nb);
}
