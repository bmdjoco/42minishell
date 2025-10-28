/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:16:59 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/28 17:31:20 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	apply_code(int err, t_env *env)
{
	char	*itoaa;

	itoaa = ft_itoa(err);
	if (!itoaa)
		return (perror("minishell: "));
	set_env_value(&env, "?", itoaa);
	free(itoaa);
}
