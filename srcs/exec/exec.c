/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:59:43 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/25 13:32:49 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	message(int err, char **argv)
{
	if (err == 126)
		ft_fprintf(2, "minishell: %s: Permission denied\n", argv[0]);
	else if (err == 127)
		ft_fprintf(2, "minishell: %s: No such file or directory\n", argv[0]);
}

static int	check_folder(char **argv)
{
	int	i;

	i = 0;
	if (!argv[0])
		return (0);
	if (argv[0] && argv[1])
		return (0);
	while (argv[0][i])
	{
		if (argv[0][i] != '/' && argv[0][i] != '.')
			return (0);
		i++;
	}
	return (1);
}

/**
*@brief recupere le path et execute la commande via execve
*@param envp tableau de strings des variables environnementales
*@param split tableau de chaines de la commade a executer
*@return le code erreur de waitpid
*/
int	doit(char **argv, char **envp)
{
	char	*path;
	pid_t	pid;
	int		err;

	path = final_path(argv, envp, &err);
	if (!path)
		return (message(err, argv), err);
	pid = fork();
	if (pid == -1)
		return (free(path), perror("minishell: "), 1);
	if (pid == 0)
	{
		exec_distributor();
		if (check_folder(argv))
		{
			1 && (free(path), ft_fprintf(2, "minishell: %s: is a directory\n", argv[0]));
			exit (126);
		}
		if (execve(path, argv, envp) == -1)
			1 && (free(path), perror("minishell: "), exit (1), 0);
	}
	1 && (doc_ignore(), free(path), err = get_code(pid));
	return (signal_distributor(), err);
}

/**
*@brief fais les commandes non built-in
*@param env liste chainee des variables environnementales
*@param split tableau de chaines de la commade a executer
*@return 0 en cas de reussite ou -1 si fail
*/
int	exec_cmd(t_env *env, char **split)
{
	char	**env_dup;
	int		err;

	env_dup = create_envp(env);
	if (!env_dup)
		return (perror("minishell: "), 1);
	err = doit(split, env_dup);
	free_split(env_dup);
	return (err);
}
