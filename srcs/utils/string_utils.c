/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:16:55 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/26 17:24:03 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_w_sep(char const *s1, char const *s2, char const sep)
{
	int		i;
	int		j;
	char	*dup;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	dup = (char *)calloc(sizeof(char), len + 2);
	if (!dup)
		return (NULL);
	i = -1;
	while (s1[++i])
		dup[i] = s1[i];
	dup[i] = sep;
	i++;
	j = -1;
	while (s2[++j])
		dup[i + j] = s2[j];
	return (dup);
}
