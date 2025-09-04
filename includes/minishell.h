/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:07:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/04 16:57:22 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../libs/ft_fprintf/ft_fprintf.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*val;

	struct s_env	*next;
}					t_env;

/* Environnement */

int		size_of_key(char *str);
int		size_of_val(char *str);
int		add_env_node(t_env **head, char *envp_line);

char	*get_env_value(t_env *env, char *key);

void	free_env(t_env *env);
void	set_env_value(t_env **env, char *key, char *val);

t_env	*init_environnement(char **envp);
t_env	*new_env_node(char *key, char *val);

/* Exec */

int		exec_cmd(t_env *env, char **split);
int		wait_for_child(pid_t pid);

char	*correct_path(char **argv, char **envp);
char	*path_len(char *s);
char	*final_path(char **argv, char **envp);

char	**get_path(char **envp);
char	**create_envp(t_env *env);

/* Readline */

int		read_lines(char **envp);
int		check_syntax_err(char *line);

/* cd */

int		builtin_cd(char **argv, t_env *env);

/* pwd */

void	builtin_pwd(void);

/* minisplit */

int		check_quotes(char *s);

char	**mini_split(char *s, t_env *env);

void	fill_str(t_env *env, char *s, int index, char *dest);

/* echo */

void	replace_and_print(char *s, t_env *env);

/* exec */

int		nb_ofredir(char **split);
int		reddir_type(char **split, int red);

char	*reddir_file(char **split, int red);

/* utils */

void	free_split(char **split);
int		is_whitespace(char c);
int		ft_strcmp(char *s1, char *s2);

/* unset */

void	unset(t_env	**env, char **split);

/* export */

void	builtin_export(t_env **env, char **split);
char	**get_args(char *s);

/* env */

void	builtin_env(t_env *env, int export);

/* exit */

int		exit_builtin(char **split);

#endif
