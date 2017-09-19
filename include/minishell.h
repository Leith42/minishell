#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"

# define PROMPT_MSG	"→ "
# define UNSETENV	"unsetenv"
# define SETENV		"setenv"
# define ECHO		"echo"
# define CD			"cd"
# define ENV		"env"
# define EXIT		"exit"

char	**g_env_var;

typedef struct	s_env
{
	char	**stdin;
	char	*home;
	t_list	*path;
}				t_env;

t_env		*get_env(char **env);
void		free_str_array(char **arr);
void		print_prompt(t_env *env);
void		free_env(t_env *env);
void		free_str_array(char **arr);
int	 		exec_commands(t_env *env);
int			ignore_command(char *cmd);
void		print_error(char *error);
int			my_setenv(t_env *env, char **args);
void		exit_minishell(t_env *env, int exit_type);
int			my_unsetenv(t_env *env, char **args);
int			get_var_line(char *var, t_env *e);
int			my_echo(char **args);
int			my_cd(t_env *env, char **args);
void		my_env(void);

#endif

