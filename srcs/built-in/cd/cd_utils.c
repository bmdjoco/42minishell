/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:55:29 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/11 15:30:45 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*join_two_strings(char *s1, char *s2, char *separator)
{
	char	*temp;
	char	*result;

	if (!s1)
		return (ft_strdup(s2));
	temp = ft_strjoin(s1, separator);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s2);
	free(temp);
	return (result);
}

char	*join_path(char **argv)
{
	char	*result;
	char	*new_result;
	int		i;

	if (!argv || !argv[0])
		return (NULL);
	result = NULL;
	i = 0;
	while (argv[i])
	{
		if (argv[i + 1])
			new_result = join_two_strings(result, argv[i], "");
		else
			new_result = join_two_strings(result, argv[i], " ");
		if (!new_result)
			return (free(result), NULL);
		free(result);
		result = new_result;
		i++;
	}
	return (result);
}
