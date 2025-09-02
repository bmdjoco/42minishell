/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:11:41 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/02 12:03:09 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *new_env_node(char *key, char *val)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

/**
 * @brief Initialiser la structure de variable environnemental
 *
 * @return renvoie le pointeur vers la structure ou NULL en cas s'erreur
 */
t_env *init_environnement(char **envp)
{
	t_env *head;
	t_env *tmp;
	t_env *new;
	int i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		char *key = ft_strndup(envp[i], size_of_key(envp[i]));
		char *val = ft_strndup(envp[i] + size_of_key(envp[i]) + 1,
				size_of_val(envp[i]));
		if (!key || !val)
			return (NULL);
		new = new_env_node(key, val);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	return (head);
}

/**
 * @brief renvoie la valeur correspondant a la cle passer en argument
 *
 * @param env liste de variable environnemental sous forme de structure s_env
 * @param key cle correspondant a la valeur rechercher
 * @return renvoie une chaine de charactere correspondant a la valleur ou NULL en cas d'erreur
 */
char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	if (!key)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (strcmp(key, tmp->key) == 0)
		{
			if (tmp->val)
				return (ft_strdup(tmp->val));
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		tmp = tmp->next;
	}
}
