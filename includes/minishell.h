/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:07:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/25 19:48:47 by bdjoco           ###   ########.fr       */
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

/* Environnement */
int	size_of_key(char *str);
int	size_of_val(char *str);

char	*get_env_value(t_env **env, char *key);

void	put_env(t_env **env);
void	free_env(t_env **env, int i, int f);

t_env	**init_environnement(char **envp);


/* CD */
int	nb_parent(char	*path);

/* pwd */
void	pwd(t_env **env);


/* minisplit */
int	check_redir(char *s);
int	get_len(char *s, int index);

char	**mini_split(char *s);

void	fill_str(char *dst, char *s, int index);


/* echo */
int	strstr_index(char *s, char *tofind);

void	echo_doc(char *end);


/* utils */
void	free_split(char **split);


#endif
