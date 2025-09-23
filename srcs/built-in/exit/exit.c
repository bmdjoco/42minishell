/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:51:45 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/23 13:24:53 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	err_check(char **split)
{
	int	i;

	if (split[2])
		return (ft_fprintf(2, "minishell: exit: too many arguments\n"), 1);
	i = 0;
	if (split[1][i] && (split[1][i] == '-' || split[1][i] == '+'))
		i++;
	while (split[1][i])
	{
		if (!ft_isdigit(split[1][i]))
			return (ft_fprintf(2,
					"minishell: exit: %c: numeric argument required\n",
					split[1][i]), 1);
		i++;
	}
	return (0);
}

void	exit_status(int status, char **split, t_env *env)
{
	free_split(split);
	free_env(env);
	rl_clear_history();
	exit (status);
}

/**
 * @brief Quitte le shell avec un code erreur specifique
 * @param split tableau de chaines avec les arguments de readline
 * @return 1 si exit est appele sans option sinon return le code specifie
 */
void	exit_builtin(char **split, t_env *env)
{
	int	err;

	err = 1;
	printf("exit\n");
	if (!split || !split[1])
		exit_status(1, split, env);
	else
	{
		err = err_check(split);
		if (err != 0)
			exit_status(1, split, env);
		err = ft_atoi(split[1]);
		if (err < 0 || err > 255)
			err = 66;
	}
	exit_status(err, split, env);
}
