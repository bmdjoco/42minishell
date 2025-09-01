/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:35:50 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/01 23:37:05 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_cd(char **argv)
{
	char *path;

	if (!argv[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];

	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
