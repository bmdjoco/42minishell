/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:19:37 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/25 12:58:31 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*join_path(char **argv, t_env *env)
{
	char	*result;
	char	*concat;
	char	*temp;

	if (!strncmp("~", argv[0], 1))
	{
		result = get_env_value(env, "HOME");
		if (!result)
			return (ft_fprintf(2, "minishell: cd: HOME not set\n"), NULL);
		concat = ft_substr(argv[0], 1, ft_strlen(argv[0]) - 1);
		if (!concat)
			return (free(result), NULL);
		temp = ft_strjoin(result, concat);
		if (!temp)
			return (free(result), free(concat), NULL);
		free(result);
		free(concat);
	}
	else
		return (ft_strdup(argv[0]));
	return (temp);
}

static char	*get_target_path(char **argv, t_env *env)
{
	char	*path;

	if (!argv[0])
	{
		path = get_env_value(env, "HOME");
		if (!path)
			return (ft_fprintf(2, "minishell: cd: HOME not set\n"), NULL);
	}
	else
	{
		path = join_path(argv, env);
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
		return (perror("minishell: "), 1);
	set_env_value(env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

static int	change_directory(char *path, t_env **env, char *old_pwd)
{
	if (chdir(path) == 0)
		return (update_pwd_vars(env, old_pwd));
	else
		return (perror("minishell: "), 1);
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

	if (argv && argv[1])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	path = get_target_path(argv, env);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (free(path), perror("minishell: "), 1);
	result = change_directory(path, &env, old_pwd);
	free(old_pwd);
	free(path);
	return (result);
}
