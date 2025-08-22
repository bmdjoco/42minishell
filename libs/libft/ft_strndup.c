/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:36:55 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 14:53:19 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	size_t	size;
	size_t	i;

	i = 0;
	if (n > (int)ft_strlen(s))
		size = ft_strlen(s) + 1;
	else
		size = n + 1;
	dup = (char *)malloc(sizeof(char) * (size));
	if (dup == NULL)
		return (NULL);
	while (i < size - 1)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
