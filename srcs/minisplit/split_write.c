/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:00:46 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/05 15:48:29 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int skip_word(char *word)
{
	int	i;

	i = 0;
	while (word[i] && !word_cond(word[i]))
	{
		i += skip_spaces(word + i);
		if (!word[i])
			break ;
		i++;
	}
	return (i);
}

static int	write_in_single(char *s, char *word, int *i)
{
	int	j;
	int	k;

	(*i)++;
	j = *i;
	k = -1;
	while (s[*i] && s[*i] != '\'')
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
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			tmp = size_of_envval(env, s + *i + 1, word);
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

static int	write_in_nothing(t_env *env, char *s, char *word, int *i)
{
	int	len;
	int	tmp;

	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '>'
		&& s[*i] != '<' && s[*i] != '|')
	{
		if (s[*i] == '$')
		{
			tmp = size_of_envval(env, s + *i + 1, word);
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

char	*write_word(t_env *env, char *s, int i)
{
	int		j;
	char	*word;

	j = get_real_word_size(env, s, 0);
	if (!j)
		return (NULL);
	word = ft_calloc(j + 1, sizeof(char));
	if (!word)
		return (perror("minishell: "), NULL);
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			j += write_in_single(s, word + j, &i);
		else if (s[i] == '"')
			j += write_in_double(env, s, word + j, &i);
		else
			j += write_in_nothing(env, s, word + j, &i);
	}
	return (word);
}
