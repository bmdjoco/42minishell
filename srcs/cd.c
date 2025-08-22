/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:19:37 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/22 16:54:42 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_pwd(char *dest)
{
	
}

int	cd(t_env **env, char *path)
{
	char	*clean_path;

	if (access(clean_path, F_OK) == -1)
		return (free(clean_path), 0);

}
