/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:55:36 by miltavar          #+#    #+#             */
/*   Updated: 2025/10/21 12:43:18 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_and_check(char **paths, char *cmd)
{
	char	*correct;
	int		i;

	i = 0;
	while (paths[i])
	{
		correct = ft_strjoin(paths[i], cmd);
		if (!correct)
			return (NULL);
		if (access(correct, X_OK) == 0)
			return (correct);
		free(correct);
		i++;
	}
	return (NULL);
}

char	*path_len(char *s)
{
	int		i;
	int		j;
	char	*full_path;

	i = 5;
	while (s[i] && s[i] != '\n')
		i++;
	j = i - 5;
	full_path = ft_calloc(j + 2, 1);
	if (!full_path)
		return (NULL);
	i = 5;
	j = 0;
	while (s[i] && s[i] != '\n')
	{
		full_path[j] = s[i];
		i++;
		j++;
	}
	full_path[j] = '\0';
	return (full_path);
}

char	**get_path(char **envp)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp = path_len(envp[i]);
			if (!temp)
				return (NULL);
			paths = ft_split(temp, ':');
			free(temp);
			if (!paths)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!paths)
		return (NULL);
	return (paths);
}

char	*correct_path(char **argv, char **envp)
{
	char	**paths;
	char	*correct;
	char	*temp;

	if (!ft_strncmp(argv[0], "./", 2) || !ft_strncmp(argv[0], "../", 3))
	{
		paths = ft_calloc(2, sizeof(char *));
		if (!paths)
			return (NULL);
		paths[0] = getcwd(NULL, 0);
		paths[1] = NULL;
	}
	else
		paths = get_path(envp);
	if (!paths)
		return (NULL);
	temp = ft_strjoin("/", argv[0]);
	if (!temp)
		return (free_split(paths), NULL);
	correct = build_and_check(paths, temp);
	if (!correct)
		return (free_split(paths), free(temp), NULL);
	return (free_split(paths), free(temp), correct);
}

int	wait_for_child(pid_t pid)
{
	int	status;
	int	sig;
	int	g_exit_status;

	status = 0;
	g_exit_status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		g_exit_status = 128 + WTERMSIG(status);
	}
	return (g_exit_status);
}
