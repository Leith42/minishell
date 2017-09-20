#include "minishell.h"

static int	print_value(char *var, t_env *env)
{
	size_t i;

	i = 0;
	while (env->env_var[i] != NULL)
	{
		if (ft_strnequ(var + 1, env->env_var[i], ft_strlen(var) - 1))
		{
			ft_putstr(env->env_var[i] + ft_strlen(var + 1) + 1);
			return (true);
		}
		i++;
	}
	return (false);
}

int			my_echo(char **args, t_env *env)
{
	size_t i;

	i = 0;
	if (args[i] == NULL)
	{
		ft_putchar('\n');
	}
	else
	{
		while (args[i] != NULL)
		{
			if (i > 0)
				ft_putchar(' ');
			if ((args[i][0] == '"') && (args[i][ft_strlen(args[i]) - 1]) == '"')
				ft_putnstr(args[i] + 1, ft_strlen((args[i] + 1)) - 1);
			else if ((args[i][0] == '$'))
				print_value(args[i], env);
			else
				ft_putstr(args[i]);
			i++;
		}
		ft_putchar('\n');
	}
	return (true);
}