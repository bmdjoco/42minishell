/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:49:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/26 17:54:49 by bdjoco           ###   ########.fr       */
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

	(void) return_code;
	if (!ft_strcmp(split[0], "unset"))
		unset(&env, split + 1);
	else if (!ft_strcmp(split[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(split[0], "env"))
		builtin_env(env, 0);
	else if (!ft_strcmp(split[0], "export"))
		builtin_export(&env, split + 1);
	else if (!ft_strcmp(split[0], "exit"))
		exit_builtin(split, env);
	else if (!ft_strcmp(split[0], "cd"))
		return (builtin_cd(split + 1, env));
	else if (!ft_strcmp(split[0], "echo"))
		echo(split + 1);
	else
		return_code = exec_cmd(env, split);
	return (0);
}

int	process_line(char *line, t_env *env)
{
	char	**split;
	int		exit;

	exit = 0;
	if (*line)
		add_history(line);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (exit);
	}
	if (check_syntax_err(line, 0) == -1)
		return (free(line), 0);
	split = mini_split(line, env);
	if (!split)
	{
		ft_fprintf(2, "minishell: split failed\n");
		free(line);
		return (0);
	}
	free(line);
	exit = do_redirections(split, env);
	free_split(split);
	return (exit);
}

/**
 * @brief Lit sur l'entree standard et redirige l'input vers les fonctions
 * @param envp environnement du terminal
 * @return code != 0 en cas d'echec, 0 si succes
 */
int	read_lines(char **envp)
{
	char	*line;
	t_env	*env;

	env = init_environnement(envp);
	if (!env)
		return (-1);
	while (1)
	{
		if (g_received_signal = SIGINT)
		{
			
		}
		else if (g_received_signal = SIGQUIT)
		{
			g_received_signal = 0;
		}
		line = readline("minishell: ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(line, env);
	}
	rl_clear_history();
	free_env(env);
	rl_cleanup_after_signal();
	return (0);
}
