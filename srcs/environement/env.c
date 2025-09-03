/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:11:41 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/03 13:34:45 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_env_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (perror("minishell: "), free(node), NULL);
	node->val = ft_strdup(val);
	if (!node->val)
		return (perror("minishell: "), free(node->key), free(node), NULL);
	node->next = NULL;
	return (node);
}

/**
 * @brief Initialiser la structure de variable environnemental
 * @return renvoie le pointeur vers la structure ou NULL en cas s'erreur
 */
t_env	*init_environnement(char **envp)
{
	t_env	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		if (add_env_node(&head, envp[i]) == -1)
			return (free_env(head), NULL);
		i++;
	}
	return (head);
}

/**
 * @brief renvoie la valeur correspondant a la cle passer en argument
 * @param env liste de variable environnemental sous forme de structure s_env
 * @param key cle correspondant a la valeur rechercher
 * @return renvoie une chaine de charactere ou NULL
 */
char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	if (!key)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
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

static void	update_existing_env(t_env *env, char *key, char *val)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->val);
			tmp->val = ft_strdup(val);
			if (!tmp->val)
				return (perror("minishell: "));
			return ;
		}
		tmp = tmp->next;
	}
}

void	set_env_value(t_env **env, char *key, char *val)
{
	t_env	*tmp;
	t_env	*new;
	char	*value;

	if (!*env)
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
	free(value);
	update_existing_env(*env, key, val);
}
