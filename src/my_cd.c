#include "minishell.h"

static void	change_oldpwd_var(char *old_pwd, t_env *env)
{
	char	*join;
	size_t	line;

	line = 0;
	while (g_env_var[line])
	{
		if ((ft_strnequ("OLDPWD=", g_env_var[line], 7)) == true)
			break ;
		line++;
	}
	if (g_env_var[line] != NULL)
	{
		if ((join = ft_strjoin("OLDPWD=", old_pwd)) == NULL)
			exit_minishell(env, EXIT_FAILURE);
		ft_strdel(&g_env_var[line]);
		g_env_var[line] = join;
	}
}

static int	change_working_dir(char *new_path, char *working_dir, t_env *env)
{
	if (chdir(new_path) == ERROR)
	{

		if (access(new_path, F_OK) == -1)
			ft_printf("cd: no such file or directory: %s\n", new_path);
		else if (access(new_path, R_OK) == -1)
			ft_printf("cd: permission denied: %s\n", new_path);
		else
			ft_printf("cd: not a directory: %s\n", new_path);
		return (false);
	}
	change_oldpwd_var(working_dir, env);
	return (true);
}

int			my_cd(t_env *env, char **args)
{
	char buffer[PATH_MAX];

	if ((getcwd(buffer, PATH_MAX)) == NULL)
		exit_minishell(env, EXIT_FAILURE);
	if (args[0] == NULL || args[0][0] == '~')
	{
		return (change_working_dir(env->home, buffer, env));
	}
	else
	{
		return (change_working_dir(args[0], buffer, env));
	}
}