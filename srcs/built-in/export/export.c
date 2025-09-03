/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:38:18 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/03 11:14:33 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_syntax(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalpha(s[i]))
		i++;
	if (!s[i] || s[i] != '=')
		return (-1);
	i++;
	if (!s[i])
		return (-1);
	return (1);
}

void	export_variable(t_env **env, char *s)
{
	char	**args;

	args = get_args(s);
	if (!args)
		return (perror("minishell: "));
	set_env_value(env, args[0], args[2]);
	free_split(args);
}

/**
 * @brief export une variable dans l'env
 * @param env l'adresse vers la liste chainee des variables d'environnement
 * @param split les chaines de caracteres a traiter
 */
void	builtin_export(t_env **env, char **split)
{
	int	i;

	if (!*split)
		builtin_env(*env, 1);
	i = 0;
	while (split[i])
	{
		if (check_syntax(split[i]) == -1)
			ft_fprintf(2, "minishell: export: %s: not a valid identifier\n");
		else
			export_variable(env, split[i]);
		i++;
	}
}
