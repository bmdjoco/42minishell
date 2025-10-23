/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:49:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/23 17:51:15 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**split_again(char **split)
{
	char	**nw_split;
	int		i;

	if (!split || !split[0])
		return (NULL);
	i = 0;
	while (split[i] && !check_limit(split[i]))
		i++;
	if (i == 0)
		return (NULL);
	nw_split = ft_calloc(i + 1, sizeof(char *));
	if (!nw_split)
		return (NULL);
	i = 0;
	while (split[i] && !check_limit(split[i]))
	{
		nw_split[i] = ft_strdup(split[i]);
		if (!nw_split[i])
			return (free_split(nw_split), NULL);
		i++;
	}
	nw_split[i] = NULL;
	return (nw_split);
}

int	parse_line(char **split, t_env *env)
{
	int		return_code;

	return_code = 0;
	if (!ft_strcmp(split[0], "unset"))
		unset(&env, split + 1);
	else if (!ft_strcmp(split[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(split[0], "env"))
		builtin_env(env, 0);
	else if (!ft_strcmp(split[0], "export"))
		return (builtin_export(&env, split + 1));
	else if (!ft_strcmp(split[0], "exit"))
		return (exit_builtin(split, env));
	else if (!ft_strcmp(split[0], "cd"))
		return (builtin_cd(split + 1, env));
	else if (!ft_strcmp(split[0], "echo"))
		echo(split + 1);
	else
		return_code = exec_cmd(env, split);
	return (return_code);
}

int	process_line(char *line, t_env *env)
{
	char	**split;
	int		exit_code;

	exit_code = 0;
	if (*line)
		add_history(line);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (exit_code);
	}
	if (check_syntax_err(line, 0) == -1)
		return (free(line), 0);
	split = mini_split(line, env);
	if (!split)
	{
		free(line);
		return (0);
	}
	free(line);
	exit_code = do_pipe(split, env);
	free_split(split);
	return (exit_code);
}

/**
 * @brief Lit sur l'entree standard et redirige l'input vers les fonctions
 * @param envp environnement du terminal
 * @return code != 0 en cas d'echec, 0 si succes
 */
int	read_lines(char **envp)
{
	int		exit_code;
	char	*line;
	t_env	*env;

	env = init_environnement(envp);
	if (!env)
		return (-1);
	1 && (exit_code = 0, signal_distributor(), 0);
	while (1)
	{
		1 && (g_received_signal = 0, line = readline("minishell: "), 0);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0')
		{
			1 && (exit_code = 0, signal_handler(exit_code), free(line), 0);
			continue ;
		}
		exit_code = process_line(line, env);
		signal_handler(exit_code);
	}
	return (rl_clear_history(), free_env(env), exit_code);
}
