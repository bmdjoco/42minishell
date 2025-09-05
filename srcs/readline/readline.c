/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:49:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/05 15:36:33 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_line(char **split, t_env *env)
{
	if (!split[0])
		return (0);
	if (!ft_strcmp(split[0], "unset"))
		unset(&env, split + 1);
	else if (!ft_strcmp(split[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(split[0], "env"))
		builtin_env(env, 0);
	else if (!ft_strcmp(split[0], "export"))
		builtin_export(&env, split + 1);
	else if (!ft_strcmp(split[0], "exit"))
		return (exit_builtin(split + 1));
	else if (!ft_strcmp(split[0], "cd"))
		return (builtin_cd(split + 1, env));
	else
		return (exec_cmd(env, split));
	// else if (!ft_strcmp(split[0], "echo"))
	// 	echo();
	return (0);
}

int	process_line(char *line, t_env *env)
{
	char	**split;
	int		exit;

	exit = 0;
	if (*line)
		add_history(line);
	//if (check_syntax_err(line) == -1)
	//{
	//	ft_fprintf(2, "minishell: syntax error near unexpected token\n");
	//	return (free(line), 1);
	//}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (exit);
	}
	split = mike_split(line, env, 0);
	if (!split)
	{
		free(line);
		return (0);
	}
	for (int i = 0; split[i]; i++)
		printf("%s\n", split[i]);
	return (0);
	free(line);
	exit = parse_line(split, env);
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
	return (0);
}
