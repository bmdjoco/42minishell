/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:33:14 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/26 20:39:15 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @return Renvoie le nombre de repertoire prent d'un path
 *
 * @param path chemin d'acces absolue
 */
int	nb_parent(char *path)
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

/**
 * @brief calcule le nombre de fois ou le path appelle un repertoire parent
 *
 * @param path chemin absolue ou relatif
 * @return 0 ou un nombre positif
 */
int	nb_of_move_up(char *path)
{
	int	i;
	int	nb;
	int	s;

	i = 0;
	nb = 0;
	s = (int) strlen(path);
	while (i < s)
	{
		if ((i + 1 == s - 1 && !ft_strncmp("..", &path[i], 2))
			|| (i + 2 < s && !ft_strncmp("../", &path[i], 3)))
		{
			nb++;
			if (i + 2 < s)
				i++;
			i++;
		}
		i++;
	}
	return (nb);
}

/**
 * @brief calcule le nombre de fois ou le path appelle un repertoire enfant
 *
 * @param path chemin absolue ou relatif
 * @return 0 ou un nombre negatif
 */
int	nb_of_move_down(char *path)
{
	int	i;
	int	nb;
	int	s;

	i = 0;
	nb = 0;
	s = (int) strlen(path);
	while (i < s)
	{
		if (i == 0 && path[i] == '/')
			;
		else if (i + 1 < s && !ft_strncmp("./", &path[i], 2))
			i += 1;
		else if (i + 2 < s && !ft_strncmp("../", &path[i], 3))
			i += 2;
		else if (i == s - 1 && path[i] == '.')
			;
		else if (i + 1 == s - 1 && !ft_strncmp("..", &path[i], 2))
			;
		else
		{
			nb--;
			while (i < s && path[i] != '/')
				i++;
		}
		i++;
	}
	return (nb);
}

/**
 * @return la difference d'appelle de repertoire parent et enfant
 */
int	nb_of_move(char *path)
{
	return (nb_of_move_up(path) + nb_of_move_down(path));
}
