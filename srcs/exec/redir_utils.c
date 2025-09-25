/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:04 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/25 15:01:59 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief renvoie le nombre de redirection de la commande
 */
int	nb_of_redir(char **split)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (split[i] && split[i][0] != '|')
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			res++;
		i++;
	}
	return (res);
}

/**
 * @brief renvoie le type de redirection a faire a la red position
 *
 * @return 1 pour >>, 2 pour >, 3 pour <, 4 pour <<
 * @return -1 en cas d'erreur
 */
int	reddir_type(char **split, int red)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red)
		{
			if (!ft_strcmp(">>", split[i]))
				return (1);
			else if (!ft_strcmp(">", split[i]))
				return (2);
			else if (!ft_strcmp("<", split[i]))
				return (3);
			else if (!ft_strcmp("<<", split[i]))
				return (4);
		}
		i++;
	}
	return (-1);
}

/**
 * @brief renvoie le nom de redirection a faire a la red position
 *
 * @return le nom du fichier de redirection
 */
char	*reddir_file(char **split, int red)
{
	int		nb;
	int		i;
	char	*res;

	nb = 0;
	i = 0;
	while (split[i] && split[i][0])
	{
		if (split[i][0] == '>' || split[i][0] == '<')
			nb++;
		if (nb == red && split[i + 1])
		{
			res = ft_strdup(split[i + 1]);
			if (!res)
				return (NULL);
			return (res);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief gere les redirections, open et distribue a parse_line
 * @param split ensemble de chaines des arguments de commande
 * @param env ensemble des variables environnementales
 * @return 1 en cas de succes, -1 en cas d'erreur
 */
int	do_redirections(char **split, t_env *env)
{
	t_redir_util	*util;

	util = malloc(sizeof(t_redir_util));
	if (!util)
		return (perror("minishell: "), -1);
	util->og_split = split;
	util->env = env;
	util->redir = nb_of_redir(split);
	if (util->redir <= 0)
		return (free(util),parse_line(split, env), 1);
	util->original[0] = dup(STDIN_FILENO);
	if (util->original[0] == -1)
		return (free(util),perror("minishell: dup"), -1);
	util->original[1] = dup(STDOUT_FILENO);
	if (util->original[1] == -1)
		return (close(util->original[0]),free(util), perror("minishell: dup"), -1);
	if (process_all_redirections(util) == -1)
		return (close(util->original[0]), close(util->original[1]), free(util), -1);
	execute_with_redirections(split, env);
	dup2(util->original[0], STDIN_FILENO);
	dup2(util->original[1], STDOUT_FILENO);
	close(util->original[0]);
	close(util->original[1]);
	free(util);
	return (1);
}
