/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:12:15 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/25 15:54:55 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_env **env)
{
	char	*pwd;

	pwd = get_env_value(env, "PWD");
	if (!pwd)
		return ;
	printf("%s", pwd);
	free(pwd);
}
