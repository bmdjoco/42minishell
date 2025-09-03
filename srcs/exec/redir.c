/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:58:55 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/03 15:04:41 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_redir(char **split, int red_type, char *file)
{
	int	infile;
	int	outfile;

	infile = 0;
	outfile = 1;
	if (red_type == 3)
		infile = open(file, O_RDONLY);
	else if (red_type == 2)
		outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red_type == 1)
		outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
}
