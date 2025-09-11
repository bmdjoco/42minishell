/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:19:37 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/11 15:26:27 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_target_path(char **argv, t_env *env)
{
	char	*path;

	if (!argv[0])
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			ft_fprintf(2, "minishell: cd: HOME not set\n");
			return (NULL);
		}
	}
	else
	{
		path = join_path(argv);
		if (!path)
			return (perror("minishell: "), NULL);
	}
	return (path);
}

static int	update_pwd_vars(t_env **env, char *old_pwd)
{
	char	*new_pwd;

	set_env_value(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("minishell: "), -1);
	set_env_value(env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

static int	change_directory(char *path, t_env **env, char *old_pwd)
{
	if (chdir(path) == 0)
		return (update_pwd_vars(env, old_pwd));
	else
	{
		ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", path);
		return (-1);
	}
}

/**
 * @param env la liste chainee des variables key value de l'environnement
 * @param argv la chaine de split avec les arguments a executer
 * @return 0 on success, -1 on error
 */
int	builtin_cd(char **argv, t_env *env)
{
	char	*path;
	char	*old_pwd;
	int		result;

	path = get_target_path(argv, env);
	if (!path)
		return (-1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("minishell: "), -1);
	result = change_directory(path, &env, old_pwd);
	free(old_pwd);
	free(path);
	return (result);
}
