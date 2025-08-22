/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:37:31 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 18:01:47 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	check_redir(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
		return (2);
	else if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
		return (2);
	else if (s[i] == '<' && !s[i + 1])
		return (1);
	else if (s[i] == '>' && !s[i + 1])
		return (1);
	else if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
		return (1);
	else if (s[i] == '>' && s[i + 1] && s[i + 1] != '>')
		return (1);
	else if (s[i] == '|' && !s[i + 1])
		return (1);
	else if (s[i] == '|' && s[i + 1])
		return (1);
	return (0);
}

int	check_dup(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] && s[i + 2]
			&& s[i + 1] == '>' && s[i + 2] == '>')
			return (ft_fprintf(2, "minishell: syntax error at '%c'", s[i]), -1);
		else if (s[i] == '|' && s[i + 1] && s[i + 2]
			&& s[i + 1] == '|' && s[i + 2] == '|')
			return (ft_fprintf(2, "minishell: syntax error at '%c'", s[i]), -1);
		i++;
	}
	return (0);
}

int	count_words(char *s)
{
	int	words;
	int	len;

	words = check_dup(s);
	if (words == -1)
		return (0);
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (!*s)
			break ;
		words++;
		len = check_redir(s);
		if (len)
			s += len;
		else
			while (*s && *s != ' ' && !check_redir(s))
				s++;
	}
	return (words);
}

/**
 * @brief split les espaces et les symboles de redirection
 * @param s une string
 * @return NULL if failed
 */
char	**mini_split(char *s)
{
	int		words;
	int		i;
	char	**res;
	int		len;

	words = count_words(s);
	if (words == 0)
		return (NULL);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < words)
	{
		len = get_len(s, i + 1);
		if (len < 0)
			return (free_split(res), NULL);
		res[i] = malloc(len + 1);
		if (!res[i])
			return (free_split(res), NULL);
		fill_str(res[i], s, i + 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}
