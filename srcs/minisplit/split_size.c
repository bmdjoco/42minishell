/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:38:40 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/06 13:11:44 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_of_envval(t_env *env, char *s, char *dest)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (s[i] && s[i] != '|' && s[i] != '>' && s[i] != '<'
		&& s[i] != '\'' && s[i] != '"' && s[i] != '$' && !is_whitespace(s[i]))
		i++;
	key = ft_substr(s, 0, i);
	if (!key)
		return (perror("minishell: "), -1);
	val = get_env_value(env, key);
	if (!val)
		return (free(key), -1);
	i = ft_strlen(val);
	if (dest)
		ft_strcat(dest, val);
	return (free(key), free(val), i);
}

static int	size_nothing(t_env *env, char *s, int *i)
{
	int	len;
	int	tmp;

	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '>'
		&& s[*i] != '<' && s[*i] != '|')
	{
		if (s[*i] == '$')
		{
			tmp = size_of_envval(env, s + *i + 1, NULL);
			if (tmp == -1)
				return (go_end(s, i), len);
			*i += skip_envkey(s + *i + 1) + 1;
			len += tmp;
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	if (s[*i] && (s[*i] == '\'' || s[*i] == '"' || s[*i] == '>'
		|| s[*i] == '<' || s[*i] == '|'))
		return (go_end(s, i), len);
	return (len);
}

static int	size_in_double(t_env *env, char *s, int *i)
{
	int	len;
	int	tmp;

	len = 0;
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			tmp = size_of_envval(env, s + *i + 1, NULL);
			if (tmp == -1)
				return (go_end(s, i), len);
			*i += skip_envkey(s + *i + 1) + 1;
			len += tmp;
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	if (s[*i] == '"')
		(*i)++;
	return (len);
}

int	get_real_word_size(t_env *env, char *s, int i)
{
	int	len;
	int	tmp;

	len = 0;
	while (s[i] && !word_cond(s[i]))
	{
		if (s[i] == '\'')
			len += size_in_single(s, &i);
		else if (s[i] == '"')
		{
			tmp = size_in_double(env, s, &i);
			if (tmp == -1)
				return (len);
			len += tmp;
		}
		else if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			tmp = size_in_double(env, s, &i);
			if (tmp == -1)
				return (len);
			len += tmp;
		}
		else
		{
			tmp = size_nothing(env, s, &i);
			if (tmp == -1)
				return (len);
			len += tmp;
		}
	}
	return (len);
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
