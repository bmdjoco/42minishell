/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:19:56 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/23 14:07:23 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	env_len(char *line, t_env *env, char *dest)
{
	int		i;
	char	*val;
	char	*temp;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?'))
		i++;
	temp = ft_calloc(i + 1, sizeof(char));
	if (!temp)
		return (0);
	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?'))
	{
		temp[i] = line[i];
		i++;
	}
	1 && (temp[i] = '\0', val = get_env_value(env, temp), free(temp), 1);
	if (!val)
		return (0);
	if (dest)
		ft_strcat(dest, val);
	i = ft_strlen(val);
	free(val);
	return (i);
}

int	skip_env(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?'))
		i++;
	return (i);
}

int	len_doc(char *line, t_env *env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			len += env_len(line + i, env, NULL);
			i += skip_env(line + i);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	fill_doc(char *dest, char *line, t_env *env)
{
	int	i;
	int	len;
	int	added;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			added = env_len(line + i, env, dest + len);
			len += added;
			i += skip_env(line + i);
		}
		else
		{
			dest[len] = line[i];
			len++;
			i++;
		}
	}
	dest[len] = '\0';
}

char	*expand_doc(char *line, t_env *env)
{
	char	*expand;
	int		len;

	if (!dollar(line))
		return (ft_strdup(line));
	len = len_doc(line, env);
	expand = ft_calloc(len + 1, sizeof(char));
	if (!expand)
		return (NULL);
	fill_doc(expand, line, env);
	return (expand);
}
