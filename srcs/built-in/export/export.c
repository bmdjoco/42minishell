/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:38:18 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/24 14:04:16 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_export(char *s, char **dest)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalpha(s[i]))
		i++;
	if (i == 0)
		return (ft_fprintf(2,
				"minishell: export: '%s': not a valid identifier\n"), -1);
	dest[0] = ft_strndup(s, i);
	if (!dest[0])
		return (perror("minishell: "), -1);
	if (!s[i])
		return (dest[1] = NULL, dest[2] = NULL, dest[3] = NULL, 1);
	if (ft_strncmp("=", s + i, 1) != 0)
		return (ft_fprintf(2,
				"minishell: export: '%s': not a valid identifier\n"), -1);
	dest[1] = ft_strndup(s + i, 1);
	if (!dest[1])
		return (perror("minishell: "), -1);
	i++;
	dest[2] = ft_strdup(s + i);
	dest[3] = NULL;
	return (1);
}

char	**get_args(char *s)
{
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	res = ft_calloc(4, sizeof(char *));
	if (!res)
		return (NULL);
	if (check_export(s, res) == -1)
		return (NULL);
	return (res);
}

int	export_variable(t_env **env, char *s)
{
	char	**args;

	args = get_args(s);
	if (!args)
		return (free_split(args), -1);
	set_env_value(env, args[0], args[2]);
	free_split(args);
	return (1);
}

/**
 * @brief export une variable dans l'env
 * @param env l'adresse vers la liste chainee des variables d'environnement
 * @param split les chaines de caracteres a traiter
 */
int	builtin_export(t_env **env, char **split)
{
	int	i;

	if (!*split)
		builtin_env(*env, 1);
	i = 0;
	while (split[i])
	{
		if (export_variable(env, split[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}
