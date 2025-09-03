/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:46:13 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/03 11:14:12 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_backslash(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	check_dollar(char *s, t_env *env)
{
	int		i;
	char	*check;
	char	*temp;

	i = 0;
	check = ft_calloc(500, 1);
	if (!check)
		return (ft_fprintf(2, "minishell: failed to alloc\n"), -1);
	while (s[i] && !is_whitespace(s[i]) && s[i] != 92)
	{
		check[i] = s[i];
		i++;
	}
	check[i] = '\0';
	temp = get_env_value(env, check);
	if (!temp)
		return (free(check), 0);
	free(check);
	printf("%s", temp);
	free(temp);
	return (i);
}

void	replace_and_print(char *s, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = check_dollar(s + i + 1, env) + 1;
			if (j == -1)
				exit (1);
			else if (j == 0)
			{
				printf("%c", s[i]);
				i++;
			}
			else
				i += j;
		}
		else
		{
			printf("%c", s[i]);
			i++;
		}
	}
}

void	print(char **split, int bs, t_env *env)
{
	int	i;

	if (bs == 1)
		i = 2;
	else
		i = 1;
	while (split[i])
	{
		replace_and_print(split[i], env);
		if (split[i + 1])
			printf(" ");
		i++;
	}
	if (bs == 1)
		printf("\n");
}

/**
 * @brief Reproduit le comportement de echo
 * @param split tableau de chaines avec la premiere etant echo
 * @param env l'environnement actuel
 * @return -1 en cas d'echec, 0 si succes
 */
// int	echo(char **split, t_env **env)
// {
// 	return (0);
// }
