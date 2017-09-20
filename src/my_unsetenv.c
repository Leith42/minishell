#include "minishell.h"

static void	del_var(int line, t_env *env)
{
	char	**new;
	size_t	i;
	size_t	n;

	i = 0;
	while (env->g_env_var[i] != NULL)
		i++;
	if ((new = ft_memalloc(sizeof(char *) * (i + 2))) == NULL)
		exit_minishell(env, EXIT_FAILURE);
	i = 0;
	n = 0;
	while (env->g_env_var[i] != NULL)
	{
		if (i != line)
		{
			if ((new[n] = ft_strdup(env->g_env_var[i])) == NULL)
				exit_minishell(env, EXIT_FAILURE);
			n++;
		}
		ft_strdel(&env->g_env_var[i]);
		i++;
	}
	free(env->g_env_var);
	env->g_env_var = new;
}

int			my_unsetenv(t_env *env, char **args)
{
	int line;

	if (args[0] == NULL || args[1] != NULL)
	{
		return (false);
	}
	line = get_var_line(ft_strjoin(args[0], "="), env);
	if (env->g_env_var[line] == NULL)
	{
		print_error("unsetenv: environment variable not found.");
		return (false);
	}
	del_var(line, env);
	return (true);
}