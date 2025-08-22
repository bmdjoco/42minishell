/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:07:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 17:54:45 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"
#include "../libs/ft_fprintf/ft_fprintf.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char	*key;
	char	*val;
}		t_env;

int	size_of_key(char *str);
int	size_of_val(char *str);
int	strstr_index(char *s, char *tofind);

char	*get_env_value(t_env **env, char *key);

char	**mini_split(char *s);

void	pwd(t_env **env);
void	echo_doc(char *end);
void	put_env(t_env **env);
void	free_env(t_env **env, int i, int f);

t_env	**init_environnement(char **envp);

#endif
