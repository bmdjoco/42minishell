/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:27:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/17 16:23:51 by miltavar         ###   ########.fr       */
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

int	expand_len(char *s, t_env *env)
{
	int			i;
	char	*temp;

	i = 0;

	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
		i++;
	temp = (i + 1, sizeof(char));
	if (!temp)
		return (perror("minishell: "), -1);
	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
	{

		i++;
	}
}

static int	real_len(char *s, t_env *env)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i += skip_single_quotes(s, i);
		else if (s[i] == '$')
			i += expand_len(s + i + 1, env);
	}
}

char	*expand_var(char *s, t_env *env)
{
	char	*res;
	char	*temp;
	int		len;

	return (NULL);
}
