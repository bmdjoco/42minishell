/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:12:15 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/01 15:36:01 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_env *env)
{
	char	*pwd;

	pwd = get_env_value(env, "PWD");
	if (!pwd || !ft_strcmp(pwd, getcwd(NULL, 0)))
	{
		if (!ft_strcmp(pwd, getcwd(NULL, 0)))
			free(pwd);
		printf("%s\n", getcwd(NULL, 0));
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
