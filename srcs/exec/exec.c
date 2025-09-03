/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:59:43 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/03 16:26:33 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*concat(char *key, char *val)
{
	char	*res;
	char	*key2;
	char	*val2;
	char	*tmp;

	key2 = ft_strdup(key);
	if (!key2)
		return (NULL);
	val2 = ft_strdup(val);
	if (!val2)
		return (free(key2), NULL);
	tmp = ft_strjoin(key2, "=");
	if (!tmp)
		return (free(val2), NULL);
	free(key2);
	key2 = tmp;
	res = ft_strjoin(key2, val2);
	if (!res)
		return (free(key2), free(val2), NULL);
	free(key2);
	free(val2);
	return (res);
}

char	*final_path(char **argv, char **envp, int j)
{
	char	*correct;
	char	**temp;

	if (!ft_strrchrr(argv[j], 47))
	{
		correct = correct_path(argv, envp, j);
		if (!correct)
			return (NULL);
	}
	else
	{
		temp = ft_split(argv[j], ' ');
		if (!temp)
			return (NULL);
		if (access(temp[0], X_OK) != 0)
		{
			perror(temp[0]);
			return (free_split(temp), NULL);
		}
		correct = ft_strdup(temp[0]);
		free_split(temp);
	}
	return (correct);
}

char	*grab_line(t_env *env, int j)
{
	char	*res;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (i == j)
		{
			res = concat(tmp->key, tmp->val);
			if (!res)
				return (NULL);
			return (res);
		}
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int	get_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**create_envp(t_env *env)
{
	char	**envpdup;
	int			i;
	int			size;

	if (!env)
		return (NULL);
	size = get_size(env);
	if (size <= 0)
		return (NULL);
	envpdup = ft_calloc(size + 1, 8);
	if (!envpdup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envpdup[i] = grab_line(env, i);
		if (!envpdup[i])
			return (free_split(envpdup), NULL);
		i++;
	}
	envpdup[i] = NULL;
	return (envpdup);
}
void	doit(char **argv, char **envp, int j)
{
	char	**cmd;
	char	*path;

	path = final_path(argv, envp, j);
	if (!path)
		exit(127);
	cmd = ft_split(argv[0], ' ');
	if (!cmd || !cmd[0])
	{
		if (cmd)
			free_split(cmd);
		free(path);
		ft_putstr_fd("Invalid command", 2);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror(cmd[0]);
		free(path);
		free_split(cmd);
		exit (1);
	}
}

/**
*@brief fais les commandes non built-in
*@param env liste chainee des variables environnementales
*@param split tableau de chaines de la commade a executer
*@return 0 en cas de reussite ou -1 si fail
*/
int	exec_cmd(t_env *env, char **split)
{
	char	**env_dup;

	(void)split;
	env_dup = create_envp(env);
	if (!env_dup)
		return (ft_fprintf(2, "minishell: failed to alloc\n"), -1);
	//doit(split, env_dup, 0);
	free_split(env_dup);
	return (0);
}
