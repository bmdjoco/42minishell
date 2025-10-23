/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:46:13 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/23 19:11:11 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_backslash(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}

void	print_strs(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(STDOUT_FILENO, s, i);
}

void	print(char **split, int bs)
{
	int	i;

	if (bs == 1)
		i = 1;
	else
		i = 0;
	while (split[i])
	{
		print_strs(split[i]);
		if (split[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (bs == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Reproduit le comportement de echo
 * @param split tableau de chaines avec la premiere etant echo
 * @param env l'environnement actuel
 * @return -1 en cas d'echec, 0 si succes
 */
int	echo(char **split)
{
	int	bs;

	bs = check_backslash(split[0]);
	print(split, bs);
	return (0);
}
