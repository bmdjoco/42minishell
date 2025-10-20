/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:27:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/20 12:34:11 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_code(pid_t pid, int i)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	if (i == 1)
		g_received_signal = exit_code;
	return (exit_code);
}

static int	skip_env(char *s)
{
	int	i;

	i = 0;

	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[0] == '?'))
		i++;
	return (i);
}

static int	env_len(char *s, t_env *env, char **dest)
{
	int		i;
	char	*str;
	char	*val;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[0] == '?'))
		i++;
	str = ft_substr(s, 0, i);
	if (!str)
		return (i);
	val = get_env_value(env, s);
	if (!val)
		return (free(str), 0);
	if (*dest)
		ft_strlcat(*dest, str, i);
	return (free(str), free(val), ft_strlen(val));
}

static int	real_len(char *s, t_env *env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			len += env_len(s + i + 1, env, NULL);
			i += skip_env(s + i + 1);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

static char	*fill_doc(int len, t_env *env, char *s)
{
	char	*res;
	int		i;
	int		y;

	i = 0;
	y = 0;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			env_len(s + i + 1, env, &res);
			i += skip_env(s + i + 1);
		}
		else
		{
			i++;
			ft_strlcat(res, s + i, 1);
		}
	}
	return (res);
}

char	*expand_var(char *s, t_env *env)
{
	char	*res;
	int		len;

	len = real_len(s, env);
	if (len == 0)
		return (NULL);
	res = fill_doc(len, env, s);
	if (!res)
		return (NULL);
	return (res);
}
