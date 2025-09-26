/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:07:28 by miltavar          #+#    #+#             */
/*   Updated: 2025/09/26 14:37:14 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../libs/ft_fprintf/ft_fprintf.h"

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*val;

	struct s_env	*next;
}					t_env;

typedef struct s_redir_util
{
	int				redir;
	int				original[2];
	char			**og_split;
	int				fd;
	int				red_type;
	char			*file;
	t_env			*env;
}	t_redir_util;

extern volatile sig_atomic_t g_received_signal;

/* Environnement */

int		size_of_key(char *str);
int		size_of_val(char *str);
int		add_env_node(t_env **head, char *envp_line);

char	*get_env_value(t_env *env, char *key);

void	free_env(t_env *env);
void	set_env_value(t_env **env, char *key, char *val);

t_env	*init_environnement(char **envp);
t_env	*new_env_node(char *key, char *val);

/* Redirection */

int		do_redirections(char **split, t_env *env);
int		open_file(int red_type, char *file);
int		apply_redirection(int red_type, int fd);
int		close_redir(int opens[2]);
int		do_heredoc(t_redir_util *util);
int		nb_of_redir(char **split);
int		reddir_type(char **split, int red);
int		apply_single_redirect(t_redir_util *util);
int		execute_with_redirections(char **split, t_env *env);
int		process_all_redirections(t_redir_util *util);

char	*reddir_file(char **split, int red);


/* Exec */

int		exec_cmd(t_env *env, char **split);
int		wait_for_child(pid_t pid);
int		check_limit(char *s);

char	*correct_path(char **argv, char **envp);
char	*path_len(char *s);
char	*final_path(char **argv, char **envp);

char	**get_path(char **envp);
char	**create_envp(t_env *env);
char	**split_again(char **split);

/* Readline */

int		read_lines(char **envp);
int		check_syntax_err(char *line, int i);
int		parse_line(char **split, t_env *env);
int		distributor(char **split, t_env *env);

/* cd */

int		builtin_cd(char **argv, t_env *env);
char	*join_path(char **argv);

/* pwd */

void	builtin_pwd(void);

/* minisplit */

int		size_of_envval(t_env *env, char *s, char *dest);
int		get_real_word_size(t_env *env, char *s, int i);
int		size_in_single(char *s, int *i);
int		skip_word(char *word);
int		skip_envkey(char *s);
int		skip_spaces(char *s);
int		count_words(char *s);
int		word_cond(char c);
int		size_of_envval(t_env *env, char *s, char *dest);
int		skip_word(char *s);
int		skip_single_quotes(char *s, int i);
int		skip_operators(char *s, int i);
int		skip_double_quotes(char *s, int i);
int		skip_unquoted_content(char *s, int i);
int		setup_redirection_fds(int *infile, int *outfile);

int		skip_env_var(char *s, int i);
void	go_end(char *s, int *i);

char	*write_word(t_env *env, char *s, int i);
char	**mini_split(char *s, t_env *env);

/* echo */

int		echo(char **split);
void	print_strs(char *s);

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

void	exit_builtin(char **split, t_env *env);

/* signal */

void	signal_handler(int sig);

#endif
