/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:11:41 by bdjoco            #+#    #+#             */
/*   Updated: 2025/10/29 16:39:36 by miltavar         ###   ########.fr       */
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
	if (!val)
		node->val = NULL;
	else
	{
		node->val = ft_strdup(val);
		if (!node->val)
			return (perror("minishell:"), free(node->key), free(node), NULL);
	}
	node->next = NULL;
	return (node);
}

int	init_empty_env(t_env **head)
{
	char	*str;
	char	*temp;

	str = getcwd(NULL, 0);
	if (!str)
		return (perror("minishell: "), -1);
	temp = ft_strjoin("PWD=", str);
	free(str);
	if (!temp)
		return (-1);
	if (add_env_node(head, temp) == -1)
		return (free(temp), -1);
	free(temp);
	return (0);
}

/**
 * @brief Initialiser la structure de variable environnemental
 * @return renvoie le pointeur vers la structure ou NULL en cas s'erreur
 */
t_env	*init_environnement(char **envp)
{
	t_env	*head;
	char	*val;
	int		i;
	int		res;

	i = -1;
	head = NULL;
	if (!*envp && init_empty_env(&head) == -1)
		return (NULL);
	while (envp && envp[++i])
		if (add_env_node(&head, envp[i]) == -1)
			return (free_env(head), NULL);
	val = get_env_value(head, "SHLVL");
	if (!val)
		set_env_value(&head, "SHLVL", "1");
	else
	{
		1 && (res = ft_atoi(val), free(val), val = ft_itoa(res + 1));
		if (!val)
			return (NULL);
		set_env_value(&head, "SHLVL", val);
		free(val);
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
		if (!ft_strcmp(key, tmp->key))
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

void	update_existing_env(t_env *env, char *key, char *val)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (val)
			{
				if (tmp->val)
					free(tmp->val);
				tmp->val = ft_strdup(val);
				if (!tmp->val)
					return (perror("minishell: "));
			}
			return ;
		}
		tmp = tmp->next;
	}
}
