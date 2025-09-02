/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:51:45 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/02 15:13:45 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Quitte le shell avec un code erreur specifique
 * @param split tableau de chaines avec les arguments de readline
 * @return 1 si exit est appele sans option sinon return l'erreur specifiee
 */
int	exit_builtin(char **split)
{
	int	err;

	err = 1;
	printf("exit\n");
	if (!split[0])
		err = 1;
	else
	{
		err = ft_atoi(split[0]);
		if (err < 0 || err > 255)
			err = 66;
		if (split[1])
			ft_fprintf(2, "bash: exit: too many arguments\n");
	}
	return (err);
}
