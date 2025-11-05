/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:49:01 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/05 15:14:53 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	parse_line(char **split, t_env *env, char **og_split)
{
	int		return_code;

	return_code = 0;
	if (!ft_strcmp(split[0], "unset"))
		unset(&env, split + 1);
	else if (!ft_strcmp(split[0], "pwd"))
		return_code = builtin_pwd();
	else if (!ft_strcmp(split[0], "env") && !split[1])
		return_code = builtin_env(env, 0, split);
	else if (!ft_strcmp(split[0], "export"))
		return_code = builtin_export(&env, split + 1);
	else if (!ft_strcmp(split[0], "exit"))
		return_code = exit_builtin(split, env, og_split);
	else if (!ft_strcmp(split[0], "cd"))
		return_code = builtin_cd(split, env);
	else if (!ft_strcmp(split[0], "echo"))
		echo(split + 1);
	else
		return_code = exec_cmd(env, split, og_split);
	return (return_code);
}

int	ignore(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		if (line[0] == '!' || line[0] == ':')
		{
			i++;
			while (line[i])
			{
				if (!is_whitespace(line[i]))
					return (0);
				i++;
			}
			return (1);
		}
	}
	return (0);
}

int	process_line(char *line, t_env *env)
{
	char		**split;
	static int	exit_code = 0;

	if (*line)
		add_history(line);
	if (ft_strlen(line) == 0)
		return (free(line), exit_code);
	if (ignore(line))
		return (free(line), 0);
	if (check_syntax_err(line, 0, 0) == -1)
		return (free(line), 2);
	split = mini_split(line, env);
	if (!split)
		return (free(line), 0);
	free(line);
	exit_code = do_pipe(split, env);
	free_split(split);
	return (apply_code(exit_code, env), exit_code);
}

/**
 * @brief Lit sur l'entree standard et redirige l'input vers les fonctions
 * @param envp environnement du terminal
 * @return code != 0 en cas d'echec, 0 si succes
 */
int	read_lines(char **envp)
{
	int		ext;
	t_env	*env;

	env = init_environnement(envp);
	if (!env)
		return (ft_fprintf(2, "minishell: malloc failed\n"), 1);
	1 && (ext = 0, apply_code(ext, env), signal_distributor(), 0);
	ext = do_loop(env);
	return (ft_fprintf(2, "exit\n"), rl_clear_history(), free_env(&env), ext);
}
