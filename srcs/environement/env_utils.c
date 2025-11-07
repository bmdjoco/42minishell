/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:49:44 by bdjoco            #+#    #+#             */
/*   Updated: 2025/11/07 12:32:53 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @return renvoie la longueur de la cle
 * @param str variable environnemental (sous forme: USER=test1)
 */
int	size_of_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

/**
 * @return renvoie la longueur de la valeur associe a la cle
 * @param str variable environnemental (sous forme: USER=test1)
 */
int	size_of_val(char *str)
{
	int	i;
	int	l;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	l = 0;
	while (str[i])
	{
		l++;
		i++;
	}
	return (l);
}

/**
 * @brief free en integraliter ou en partis la structure s_env
 * @param env liste de variable environnemental sous forme de structure s_env
 */
void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->val)
			free((*env)->val);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

/**
 * @brief Cree et ajoute un nouveau noeud a la liste d'environnement
 * @param head pointeur vers la tete de liste
 * @param envp_line ligne d'environnement a parser
 * @return 0 en cas de succes, -1 en cas d'erreur
 */
int	add_env_node(t_env **head, char *envp_line)
{
	t_env	*new;
	t_env	*tmp;
	char	*key;
	char	*val;

	key = ft_strndup(envp_line, size_of_key(envp_line));
	val = ft_strndup(envp_line + size_of_key(envp_line) + 1,
			size_of_val(envp_line));
	if (!key || !val)
		return (free(key), free(val), -1);
	new = new_env_node(key, val);
	free(key);
	free(val);
	if (!new)
		return (-1);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

void	set_env_value(t_env **env, char *key, char *val)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*check;
	char	*value;

	if (!env || !*env || !key)
		return ;
	tmp = *env;
	value = get_env_value(*env, key);
	if (!value)
	{
		while (tmp->next)
			tmp = tmp->next;
		new = new_env_node(key, val);
		if (!new)
			return (perror("minishell: "));
		tmp->next = new;
		return ;
	}
	1 && (free(value), check = *env);
	while (check && ft_strcmp(check->key, key))
		check = check->next;
	if (!check)
		return ;
	update_existing_env(*env, key, val);
}
