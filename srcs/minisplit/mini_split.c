/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:06:48 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/22 14:48:54 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**mini_split(char *s, t_env *env)
{
	int		i;
	int		j;
	int		len;
	char	**split;

	len = count_words(s);
	if (len == 0)
		return (NULL);
	split = ft_calloc(len + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	j = 0;
	j += skip_spaces(s);
	while (++i < len)
	{
		split[i] = write_word(env, s + j, 0);
		if (!split[i])
			return (free_split(split), NULL);
		j += skip_word(s + j);
		j += skip_spaces(s + j);
	}
	split[i] = NULL;
	return (split);
}

void	match_word(char *s, int *i)
{
	while (s[(*i)] && !word_cond(s[(*i)]))
	{
		if (s[(*i)] && s[(*i)] == '\'')
		{
			(*i)++;
			while (s[(*i)] && s[(*i)] != '\'')
				(*i)++;
			(*i)++;
		}
		else if (s[(*i)] && s[(*i)] == '"')
		{
			(*i)++;
			while (s[(*i)] && s[(*i)] != '"')
				(*i)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}

int	count_words(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		i += skip_spaces(s + i);
		if (!s[i])
			break ;
		if ((s[i]) && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
		{
			word++;
			while ((s[i]) && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
				i++;
		}
		else
		{
			match_word(s, (&i));
			word++;
		}
	}
	return (word);
}

int	size_of_envval(t_env *env, char *s, char *dest)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	key = ft_substr(s, 0, i);
	if (!key)
		return (perror("minishell: "), -1);
	val = get_env_value(env, key);
	if (!val)
		return (free(key), 0);
	i = ft_strlen(val);
	if (dest)
		ft_strcat(dest, val);
	return (free(key), free(val), i);
}

int	skip_word(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
		return (skip_operators(s, i));
	while (s[i] && !word_cond(s[i]))
	{
		if (s[i] == '\'')
			i = skip_single_quotes(s, i);
		else if (s[i] == '"')
			i = skip_double_quotes(s, i);
		else
			i = skip_unquoted_content(s, i);
	}
	return (i);
}
