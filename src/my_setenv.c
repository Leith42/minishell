#include "minishell.h"

int			get_var_line(char *var, t_env *env)
{
	int		i;
	size_t	var_len;

	if (var == NULL)
		exit_minishell(env, EXIT_FAILURE);
	i = 0;
	var_len = ft_strlen(var);
	while (env->g_env_var[i] != NULL)
	{
		if ((ft_strnequ(var, env->g_env_var[i], var_len)) == true)
			break ;
		i++;
	}
	ft_strdel(&var);
	return (i);
}

static int	new_and_cpy(int size, char *variable, t_env *env)
{
	size_t i;
	char **new;

	if ((new = ft_memalloc(sizeof(char *) * (size))) == NULL)
		return (ERROR);
	i = 0;
	while (env->g_env_var[i] != NULL)
	{
		if ((new[i] = ft_strdup(env->g_env_var[i])) == NULL)
			return (ERROR);
		ft_strdel(&env->g_env_var[i]);
		i++;
	}
	new[i] = variable;
	free(env->g_env_var);
	env->g_env_var = new;
	return (true);
}

void		add_new_var(int line, char **args, t_env *env)
{
	char *name;
	char *name_and_value;

	name = ft_strjoin(args[0], "=");
	if ((args[1][0] == '"') && (args[1][ft_strlen(args[1]) - 1]) == '"')
	{
		if (name == NULL || (name_and_value = ft_strjoin(name, args[1] + 1)) == NULL)
			exit_minishell(env, EXIT_FAILURE);
		name_and_value[ft_strlen(name_and_value) - 1] = '\0';
	}
	else
		if (name == NULL || (name_and_value = ft_strjoin(name, args[1])) == NULL)
			exit_minishell(env, EXIT_FAILURE);
	ft_strdel(&name);
	if (env->g_env_var[line] != NULL)
	{
		ft_strdel(&env->g_env_var[line]);
		env->g_env_var[line] = name_and_value;
	}
	else
	{
		if ((new_and_cpy(line + 2, name_and_value, env)) == ERROR)
			exit_minishell(env, EXIT_FAILURE);
	}
}

int			my_setenv(t_env *env, char **args)
{
	int line;

	if ((args[0] == NULL) || (args[1] == NULL) || (args[2] != NULL))
	{
		print_error("unsetenv: invalid number of arguments.\nusage: unsetenv [name] [value]");
		return (false);
	}
	line = get_var_line(ft_strjoin(args[0], "="), env);
	add_new_var(line, args, env);
	return (true);
}