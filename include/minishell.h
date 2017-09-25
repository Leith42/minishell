/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:05:39 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 12:06:29 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"

# define PROMPT_MSG	"\033[31m→\033[0m "
# define UNSETENV	"unsetenv"
# define SETENV		"setenv"
# define ECHO		"echo"
# define CD			"cd"
# define ENV		"env"
# define EXIT		"exit"

typedef struct	s_env
{
	char	**env_var;
	char	**stdin;
}				t_env;

t_env			*get_env(char **env);
void			free_str_array(char **arr);
void			print_prompt(t_env *env);
void			free_env(t_env *env);
void			free_str_array(char **arr);
int				exec_commands(t_env *env);
int				ignore_command(char *cmd);
void			print_error(char *error);
int				my_setenv(t_env *env, char **args);
void			exit_minishell(t_env *env, int exit_type);
int				my_unsetenv(t_env *env, char **args);
size_t			get_var_line(char *var, t_env *e);
int				my_echo(char **args, t_env *env);
int				my_cd(t_env *env, char **args);
void			my_env(t_env *env);
char			*get_home(t_env *env);
char			**get_path(t_env *env);
void			free_lst(void *content, size_t n);
char			*get_old_pwd(t_env *env);
void			trim_str_array(char **arr, t_env *env);
void			replace_tabs_by_spaces(char *str);
void			parent_signal(int signal);
void			child_signal(int code);

#endif
