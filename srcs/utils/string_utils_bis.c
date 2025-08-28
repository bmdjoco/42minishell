/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:17:41 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/28 14:20:46 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_size_res_re(char const *str, char *to_cut, char *re)
{
	int		i;
	int		s;
	size_t	cut_s;

	cut_s = ft_strlen(to_cut);
	i = -1;
	s = 0;
	while (str[++i])
	{
		if (ft_strncmp(str, to_cut, cut_s) == 0)
			i += (int) cut_s - 1;
		else
			s++;
	}
	return (s);
}
/**
 * @brief strchr and replace
 */
char	*ft_strchr_and_re(char const *str, char *to_cut, char *re)
{
	int		i;
	int		s;
	int		str_s;
	size_t	cut_s;
	char	*res;

	str_s = (int) ft_strlen(str);
	cut_s = ft_strlen(to_cut);
	res = (char *) calloc(get_size_res(str, to_cut) + 1, sizeof(char));
	if (!res)
		return (ft_fprintf(2, "minishell: calloc error\n"), NULL);
	i = -1;
	s = 0;
	while (str[++i])
	{
		if (i + ((int) cut_s - 1) < str_s
			|| ft_strncmp(str, to_cut, cut_s) == 0)
			i += (int) cut_s - 1;
		else
		{
			res[s] = str[i];
			s++;
		}
	}
	return (res);
}
