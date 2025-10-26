/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:12:05 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/26 14:24:08 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_in_single(char *s, char *word, int *i)
{
	int	j;
	int	k;

	(*i)++;
	j = *i;
	k = -1;
	while (s[*i] && s[*i] != '\'' && backs_cond(s, *i))
	{
		word[++k] = s[*i];
		(*i)++;
	}
	if (s[*i] == '\'')
		(*i)++;
	return (*i - (j + 1));
}

static int	write_in_double(t_env *env, char *s, char *word, int *i)
{
	int	len;
	int	tmp;

	len = 0;
	(*i)++;
	while (s[*i] && s[*i] != '"' && backs_cond(s, *i))
	{
		if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != '$' && backs_cond(s, *i))
		{
			tmp = size_of_envval(env, s + *i + 1, word + len);
			if (tmp == -1)
				return (go_end(s, i), len);
			*i += skip_envkey(s + *i + 1) + 1;
			len += tmp;
		}
		else
		{
			word[len] = s[*i];
			len++;
			(*i)++;
		}
	}
	if (s[*i] == '"')
		(*i)++;
	return (len);
}

static int	write_in_nothing(t_env *env, char *s, char *word, int *i)
{
	int	len;
	int	tmp;

	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '>'
		&& s[*i] != '<' && s[*i] != '|' && !is_whitespace(s[*i])
		&& backs_cond(s, *i))
	{
		if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != '$' && backs_cond(s, *i))
		{
			tmp = size_of_envval(env, s + *i + 1, word + len);
			if (tmp == -1)
				return (go_end(s, i), len);
			*i += skip_envkey(s + *i + 1) + 1;
			len += tmp;
		}
		else
		{
			word[len] = s[*i];
			len++;
			(*i)++;
		}
	}
	return (len);
}

static char	*write_operators(char *s, int *i, char *word)
{
	int	j;

	j = 0;
	while (s[*i] && (s[*i] == '>' || s[*i] == '<' || s[*i] == '|'))
	{
		word[j] = s[*i];
		j++;
		(*i)++;
	}
	return (word);
}

char	*write_word(t_env *env, char *s, int i)
{
	int		j;
	char	*word;

	j = get_real_word_size(env, s, i);
	word = ft_calloc(j + 1, sizeof(char));
	if (!word)
		return (perror("minishell: "), NULL);
	j = 0;
	if (s[i] && (s[i] == '>' || s[i] == '<' || s[i] == '|') && backs_cond(s, i))
		return (write_operators(s, &i, word));
	while (s[i] && !word_cond(s[i]) && backs_cond(s, i))
	{
		if (s[i] == '\'' && backs_cond(s, i))
			j += write_in_single(s, word + j, &i);
		else if (s[i] == '"' && backs_cond(s, i))
			j += write_in_double(env, s, word + j, &i);
		else
			j += write_in_nothing(env, s, word + j, &i);
	}
	return (word);
}
