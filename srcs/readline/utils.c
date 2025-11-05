/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:16:59 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/05 14:46:25 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	apply_code(int err, t_env *env)
{
	char	*itoaa;

	itoaa = ft_itoa(err);
	if (!itoaa)
		return (perror("minishell: "));
	set_env_value(&env, "?", itoaa);
	free(itoaa);
}

int	is_exit(char *line)
{
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len < 4)
		return (0);
	if (line[0] == 'e' && line[1] == 'x'
		&& line[2] == 'i' && line[3] == 't'
		&& line[4] == '\0')
		return (1);
	return (0);
}

int	do_loop(t_env *env)
{
	static int	ext = 0;
	char		*line;

	while (1)
	{
		1 && (g_received_signal = 0, line = readline("minishell: "), 0);
		if (!line)
			break ;
		if (g_received_signal == 130)
			1 && (apply_code(130, env), ext = 130);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (is_exit(line) == 1)
			1 && (ft_fprintf(2, "exit\n"), free_env(&env), free(line),
				rl_clear_history(), exit(ext), 0);
		1 && (ext = process_line(line, env), signal_handler(ext), 0);
	}
	return (ext);
}

void	syntax_msg(char c)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", c);
}

int	check_limit(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (1);
	else if (!ft_strcmp(s, "<"))
		return (1);
	else if (!ft_strcmp(s, "<<"))
		return (1);
	else if (!ft_strcmp(s, ">>"))
		return (1);
	else if (!ft_strcmp(s, "|"))
		return (1);
	return (0);
}
