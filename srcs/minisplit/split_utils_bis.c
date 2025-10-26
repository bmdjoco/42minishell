/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:06:34 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/26 14:55:30 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief renvoie 0 (vrai) si le caractere i - 1 de la chaine n'est pas un
 * backslash ou si la chaine est aux debut sinon 1 (faux) si le charactere
 * precedent est backslash
 */
int	backs_cond(char *s, int i)
{
	if (i == 0 || (i - 1 >= 0 && s[i - 1] != '\\'))
		return (0);
	return (1);
}
