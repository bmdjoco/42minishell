/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:19:37 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/03 12:36:53 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @param env la liste chainee des variables key value de l'environnement
 * @param path ?
 * @return ?
 */
int	builtin_cd(char **argv, t_env *env)
{
	char	*path;
	char	*tmp;

	if (!argv[1])
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];
	tmp = getcwd(NULL, 0);
	if(!tmp)
		fprintf(stderr, "minishell: cd: malloc error\n");
	if (chdir(path) != 0)
	{
		set_env_value(&env, "OLDPATH", tmp);
		free(tmp);
		tmp = getcwd(NULL, 0);
		if(!tmp)
			fprintf(stderr, "minishell: cd: malloc error\n");
		set_env_value(&env, "PATH", tmp);
		ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	if (!argv[1])
		free(path);
	return (free(tmp), 0);
}
