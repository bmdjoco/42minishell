/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:12:15 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/03 11:14:56 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief affiche le chemin actuellent utilise par le terminal
 */
void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}
