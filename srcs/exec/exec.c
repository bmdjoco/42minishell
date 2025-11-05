/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:59:43 by miltavar          #+#    #+#             */
/*   Updated: 2025/11/05 14:44:36 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_errno(void)
{
	if (errno == ENOENT)
		return (127);
	else if (errno == EACCES)
		return (126);
	else
		return (1);
}

/**
*@brief recupere le path et execute la commande via execve
*@param envp tableau de strings des variables environnementales
*@param split tableau de chaines de la commade a executer
*@return le code erreur de waitpid
*/
int	doit(char **argv, char **envp, char **og_split, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		ext;

	path = final_path(argv, envp);
	if (!path)
		return (perror("minishell: "), get_errno());
	pid = fork();
	if (pid == -1)
		return (free(path), perror("minishell: "), 1);
	if (pid == 0)
	{
		exec_distributor();
		execve(path, argv, envp);
		1 && (free_env(&env), free_split(og_split),
			free(path), free_split(argv),
			free_split(envp), perror("minishell: "), 0);
		exit (get_errno());
	}
	1 && (doc_ignore(), free(path), ext = get_code(pid));
	return (signal_distributor(), ext);
}

/**
*@brief fais les commandes non built-in
*@param env liste chainee des variables environnementales
*@param split tableau de chaines de la commade a executer
*@return 0 en cas de reussite ou -1 si fail
*/
int	exec_cmd(t_env *env, char **split, char **og_split)
{
	char	**env_dup;
	int		err;

	env_dup = create_envp(env);
	if (!env_dup)
		return (perror("minishell: "), 1);
	err = doit(split, env_dup, og_split, env);
	free_split(env_dup);
	return (err);
}
