/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:52:21 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 17:55:22 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_spaces(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

static int	redir_or_word_len(char *s, int i)
{
	int	len;

	len = check_redir(s + i);
	if (len)
		return (len);
	len = 0;
	while (s[i + len] && s[i + len] != ' ' && !check_redir(s + i + len))
		len++;
	return (len);
}

int	get_len(char *s, int index)
{
	int	i;
	int	words;
	int	len;

	i = 0;
	words = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		len = redir_or_word_len(s, i);
		words++;
		if (words == index)
			return (len);
		i += len;
	}
	return (-1);
}

static int	copy_word(char *s, int i, char *dst)
{
	int	redir_len;
	int	j;

	redir_len = check_redir(s + i);
	if (redir_len)
	{
		j = 0;
		while (j < redir_len)
		{
			dst[j] = s[i + j];
			j++;
		}
		dst[j] = '\0';
		return (redir_len);
	}
	j = 0;
	while (s[i + j] && s[i + j] != ' ' && !check_redir(s + i + j))
	{
		dst[j] = s[i + j];
		j++;
	}
	dst[j] = '\0';
	return (j);
}

void	fill_str(char *dst, char *s, int index)
{
	int	i;
	int	words;
	int	len;

	i = 0;
	words = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		len = redir_or_word_len(s, i);
		words++;
		if (words == index)
		{
			copy_word(s, i, dst);
			return ;
		}
		i += len;
	}
	if (dst)
		dst[0] = '\0';
}
