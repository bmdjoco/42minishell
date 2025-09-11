/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:04 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/11 11:34:54 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief renvoie le nombre de redirection de la commande
 */
int	nb_of_redir(char **split)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (split[i] && split[i][0] != '|')
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			res++;
		i++;
	}
	return (res);
}

/**
 * @brief renvoie le type de redirection a faire a la red position
 *
 * @return 1 pour >>, 2 pour >, 3 pour <, 4 pour <<
 * @return -1 en cas d'erreur
 */
int	reddir_type(char **split, int red)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red)
		{
			if (!ft_strcmp(">>", split[i]))
				return (1);
			else if (!ft_strcmp(">", split[i]))
				return (2);
			else if (!ft_strcmp("<", split[i]))
				return (3);
			else if (!ft_strcmp("<<", split[i]))
				return (4);
		}
		i++;
	}
	return (-1);
}

/**
 * @brief renvoie le nom de redirection a faire a la red position
 *
 * @return le nom du fichier de redirection
 */
char	*reddir_file(char **split, int red)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red && split[i + 1])
			return (ft_strdup(split[i + 1]));
		i++;
	}
	return (NULL);
}
