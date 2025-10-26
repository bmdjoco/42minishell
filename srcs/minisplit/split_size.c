/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:38:40 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/26 11:13:03 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	size_nothing(t_env *env, char *s, int *i)
{
	int	len;
	int	tmp;

	len = 0;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '>'
		&& s[*i] != '<' && s[*i] != '|' && !is_whitespace(s[*i]))
	{
		if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != '$')
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
		if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != '$')
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

static int	handle_operator_size(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
	{
		len++;
		i++;
	}
	return (len);
}

static int	process_quote_content(t_env *env, char *s, int *i, int *len)
{
	int	tmp;

	if (s[*i] == '\\' && s[*i + 1])
	{
		(*i) += 2;
		(*len)++;
	}
	else if (s[*i] == '\'')
		*len += size_in_single(s, i);
	else if (s[*i] == '"')
	{
		tmp = size_in_double(env, s, i);
		if (tmp == -1)
			return (-1);
		*len += tmp;
	}
	else
	{
		tmp = size_nothing(env, s, i);
		if (tmp == -1)
			return (-1);
		*len += tmp;
	}
	return (0);
}

int	get_real_word_size(t_env *env, char *s, int i)
{
	int	len;

	len = 0;
	if (s[i] && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
		return (handle_operator_size(s, i));
	while (s[i] && !word_cond(s[i]))
	{
		if (process_quote_content(env, s, &i, &len) == -1)
			return (len);
	}
	return (len);
}
