#include "minishell.h"

int			get_var_line(char *var, t_env *e)
{
	int		i;
	size_t	var_len;

	if (var == NULL)
		exit_minishell(e, EXIT_FAILURE);
	i = 0;
	var_len = ft_strlen(var);
	while (g_env_var[i] != NULL)
	{
		if ((ft_strnequ(var, g_env_var[i], var_len)) == true)
			break ;
		i++;
	}
	ft_strdel(&var);
	return (i);
}

static int	new_and_cpy(int size, char *variable)
{
	size_t i;
	char **new;

	if ((new = ft_memalloc(sizeof(char *) * (size))) == NULL)
		return (ERROR);
	i = 0;
	while (g_env_var[i] != NULL)
	{
		if ((new[i] = ft_strdup(g_env_var[i])) == NULL)
			return (ERROR);
		ft_strdel(&g_env_var[i]);
		i++;
	}
	new[i] = variable;
	free(g_env_var);
	g_env_var = new;
	return (true);
}

void		add_new_var(int line, char **args, t_env *e)
{
	char *name;
	char *name_and_value;

	if (!(name = ft_strjoin(args[0], "=")) || !(name_and_value = ft_strjoin(name, args[1])))
		exit_minishell(e, EXIT_FAILURE);
	ft_strdel(&name);
	if (g_env_var[line] != NULL)
	{
		ft_strdel(&g_env_var[line]);
		g_env_var[line] = name_and_value;
	}
	else
	{
		if ((new_and_cpy(line + 2, name_and_value)) == ERROR)
			exit_minishell(e, EXIT_FAILURE);
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