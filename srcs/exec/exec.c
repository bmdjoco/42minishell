/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:59:43 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/21 18:12:23 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	path = final_path(argv, envp);
	if (!path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", argv[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (free(path), perror("minishell: fork: "), 1);
	if (pid == 0)
	{
		exec_distributor();
		if (execve(path, argv, envp) == -1)
		{
			free(path);
			perror("minishell: execve: ");
			return (1);
		}
	}
	return (free(path), get_code(pid));
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
	char	**nw_split;
	int		err;

	nw_split = split_again(split);
	if (!nw_split)
		return (perror("minishell: "), 1);
	env_dup = create_envp(env);
	if (!env_dup)
		return (perror("minishell: "), 1);
	err = doit(nw_split, env_dup);
	free_split(env_dup);
	free_split(nw_split);
	return (err);
}
