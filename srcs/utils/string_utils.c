/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:16:55 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/28 14:10:38 by bdjoco           ###   ########.fr       */
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

static int	get_size_res_cut(char const *str, char *to_cut)
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

char	*ft_strchr_and_cut(char const *str, char *to_cut)
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

char	*ft_strchr_and_cut(char const *str, char *to_cut)
{
	int		i;
	int		s;
	int		str_s;
	size_t	cut_s;
	char	*res;

	str_s = (int) ft_strlen(str);
	cut_s = ft_strlen(to_cut);
	res = (char *) calloc(get_size_res_cut(str, to_cut) + 1, sizeof(char));
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

/**
 * @return renvoie 0si la chaine tofind n'est pas trouver dans str
 * ou le nombre de fois ou elle a ete trouvais dans le cas contraire
 */
int	ft_strfind(char *str, char *tofind)
{
	int		i;
	int		nb;
	int		str_s;
	size_t	find_s;

	i = 0;
	nb = 0;
	str_s = (int) ft_strlen(str);
	find_s = ft_strlen(tofind);
	i = -1;
	while (str[++i])
		if (i + ((int) find_s - 1) < str_s
			|| ft_strncmp(str, tofind, find_s) == 0)
		{
			i += (int) find_s - 1;
			nb++;
		}
	return (nb);
}
