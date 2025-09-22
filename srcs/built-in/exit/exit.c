/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:51:45 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/22 14:47:42 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	err_check(char **split)
{
	int	i;

	if (split[1])
		return (ft_fprintf(2, "minishell: exit: too many arguments\n"), 1);
	i = 0;
	if (split[0][i] && (split[0][i] == '-' || split[0][i] == '+'))
		i++;
	while (split[0][i])
	{
		if (!ft_isdigit(split[0][i]))
			return (ft_fprintf(2,
					"minishell: exit: %c: numeric argument required\n",
					split[0][i]), 1);
		i++;
	}
	return (0);
}

/**
 * @brief Quitte le shell avec un code erreur specifique
 * @param split tableau de chaines avec les arguments de readline
 * @return 1 si exit est appele sans option sinon return le code specifie
 */
int	exit_builtin(char **split)
{
	int	err;

	printf("exit\n");
	if (!split[0])
		return (1);
	else
	{
		err = err_check(split);
		if (err != 0)
			return (1);
		err = ft_atoi(split[0]);
		if (err < 0 || err > 255)
			err = 66;
	}
	return (err);
}
