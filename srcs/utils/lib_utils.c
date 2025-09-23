/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:26:14 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/23 13:55:05 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Compare deux chaines de caracteres
 * @param s1 premiere chaine
 * @param s2 deuxieme chaine
 * @return renvoie 0 si les chaines sont egales,
 * un positif si s1 est plus grand que s2,
 * un negatif si s2 est plus grande que s1
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * @brief Check les whitespaces d'un char c
 * @param c char a tester
 * @return renvoie 1 si c'est un whitespace sinon 0
 */
int	is_whitespace(char c)
{
	if (c == ' ' || c == 9 || c == 10 || c == 11 || c == 12 || c == 13)
		return (1);
	return (0);
}

/**
 * @brief Free correctement toutes les chaines d'un split et le pointeur tableau
 * @param split le pointeur vers le tableau a free
 * @return void
 */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
