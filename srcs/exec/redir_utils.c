/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:04 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/17 15:48:27 by miltavar         ###   ########.fr       */
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
	int		nb;
	pid_t	pid;

		nb = nb_of_redir(split);
	if (nb <= 0)
		return (parse_line(split, env));
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (process_all_redirections(nb, split, env) == -1)
		{
			free_env(env);
			free_split(split);
			exit (1);
		}
		exit (execute_with_redirections(split, env));
	}
	return (get_code(pid, 1));
}

int	nb_of_pipe(char **split)
{
	int	i;
	int	res;

	res = 0;
	i = -1;
	while (split[++i])
		if (!ft_strcmp(split[i], "|"))
			res++;
	return (res);
}
