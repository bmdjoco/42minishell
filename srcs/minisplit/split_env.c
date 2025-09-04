/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:01:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/04 17:13:24 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_spaces(char *s)
{
	int	v;

	v = 0;
	while (s[v] && is_whitespace(s[v]))
		v++;
	return (v);
}

int	check_cond(char c)
{
	if (c && c != '|' && c != '>'
		&& c != '<')
		return (1);
	return (0);
}

int	single(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] && s[i] == '\'')
				i++;
			else
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	doubles(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] && s[i] == '"')
				i++;
			else
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	check_quotes(char *s)
{
	int	i;

	i = single(s);
	if (i == -1)
		return (-1);
	i = doubles(s);
	if (i == -1)
		return (-1);
	return (0);
}

int	check_dup(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = check_quotes(s);
	if (i == -1)
		return (ft_fprintf(2, "minishell: syntax error at '%c'", s[i]), -1);
	while (s[i])
	{
		if (s[i] == ';')
			return (ft_fprintf(2, "minishell: syntax error at '%c'", s[i]), -1);
		else if (s[i] == '>' && s[i + 1] && s[i + 2]
			&& s[i + 1] == '>' && s[i + 2] == '>')
			return (ft_fprintf(2, "minishell: syntax error at '%c'", s[i]), -1);
		else if (s[i] == '|' && s[i + 1] && s[i + 2]
			&& s[i + 1] == '|' && s[i + 2] == '|')
			return (ft_fprintf(2, "minishell: syntax error at '%c'", s[i]), -1);
		i++;
	}
	return (0);
}

int	count_word(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = check_dup(s);
	if (word == -1)
		return (-1);
	while (s[i])
	{
		i += skip_spaces(s + i);
		if (!s[i])
			break ;
		word++;
		if (check_cond(s[i]) && !is_whitespace(s[i]))
			while (check_cond(s[i]) && !is_whitespace(s[i]))
				i++;
		else
			i++;
	}
	return (word);
}

int	size_of_quote(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
		if (s[i] == '"')
			i++;
		return (i - 2);
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		if (s[i] == '\'')
			i++;
		return (i - 2);
	}
	return (0);
}

int	check_dollar(t_env *env, char *s, char *dest)
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
		return (free(key), perror("minishell: "), -1);
	i = ft_strlen(val);
	if (dest)
		ft_strcat(dest, val);
	return (free(key), free(val), i);
}

int	skip_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '|' && s[i] != '>' && s[i] != '<'
		&& s[i] != '\'' && s[i] != '"' && s[i] != '$' && !is_whitespace(s[i]))
		i++;
	return (i);
}

int	double_case(char *s, t_env *env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$' && s[i + 1])
		{
			j = check_dollar(env, s + i + 1, NULL);
			if (j == -1)
				return (-1);
			len += j;
			i += skip_dollar(s + i);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	single_case(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\'')
		i++;
	return (i);
}

int	nothing_case(char *s, t_env *env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (s[i] && !is_whitespace(s[i])
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '$' && s[i + 1])
		{
			j = check_dollar(env, s + i + 1, NULL);
			if (j == -1)
				return (-1);
			len += j;
			i += skip_dollar(s + i);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	size_word(t_env *env, char *s)
{
	if (s[0] == '"')
		return (double_case(s + 1, env));
	else if (s[0] == '\'')
		return (single_case(s + 1));
	else
		return (nothing_case(s, env));
}

int	size_of_word_nb(t_env *env, char *s, int nb, int i)
{
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		i += skip_spaces(s + i);
		if (!s[i])
			break ;
		word++;
		if (word == nb)
			return (size_word(env, s + i));
		if (s[i] == '\'' || s[i] == '"')
		{
			if (size_of_quote(s + i) == -1)
				return (-1);
			i += size_of_quote(s + i) + 2;
		}
		else if (check_cond(s[i]))
			while (check_cond(s[i]))
				i++;
		else
			i++;
	}
	return (-1);
}

void	double_case_copy(char *src, t_env *env, char *dest)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (src[i] && src[i] != '"')
	{
		if (src[i] == '$' && src[i + 1])
		{
			j = check_dollar(env, src + i + 1, dest);
			if (j == -1)
				return ;
			len += j;
			i += skip_dollar(src + i);
		}
		else
			dest[len++] = src[i++];
	}
}

void	single_case_copy(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\'')
	{
		dest[i] = src[i];
		i++;
	}
}

void	nothing_case_copy(char *src, t_env *env, char *dest)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (src[i] && !is_whitespace(src[i])
		&& src[i] != '|' && src[i] != '<' && src[i] != '>')
	{
		if (src[i] == '$' && src[i + 1])
		{
			j = check_dollar(env, src + i + 1, dest);
			if (j == -1)
				return ;
			len += j;
			i += skip_dollar(src + i);
		}
		else
			dest[len++] = src[i++];
	}
}

void	copy_word(char *src, char *dest, t_env *env)
{
	if (src[0] == '"')
		return (double_case_copy(src + 1, env, dest));
	else if (src[0] == '\'')
		return (single_case_copy(src + 1, dest));
	else
		return (nothing_case_copy(src, env, dest));
}

void	fill_str(t_env *env, char *s, int index, char *dest)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		i += skip_spaces(s + i);
		if (!s[i])
			break ;
		words++;
		if (words == index)
			return (copy_word(s + i, dest, env));
		if (s[i] == '\'' || s[i] == '"')
		{
			if (size_of_quote(s + i) == -1)
				return ;
			i += size_of_quote(s + i) + 2;
		}
		else if (check_cond(s[i]))
			while (check_cond(s[i]))
				i++;
		else
			i++;
	}
}

/**
 * @brief split les espaces et les symboles de redirection
 * @param s une string
 * @return NULL if failed
 */
char	**mini_split(char *s, t_env *env)
{
	int		words;
	int		i;
	char	**res;
	int		len;

	words = count_word(s);
	if (words == 0)
		return (NULL);
	res = ft_calloc(words + 1, 8);
	if (!res)
		return (perror("minishell: "), NULL);
	i = 0;
	while (i < words)
	{
		len = size_of_word_nb(env, s, i + 1, 0);
		if (len < 0)
			return (free_split(res), printf("\n"), NULL);
		res[i] = ft_calloc(len + 1, 1);
		if (!res[i])
			return (perror("minishell: "), free_split(res), NULL);
		fill_str(env, s, i + 1, res[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
