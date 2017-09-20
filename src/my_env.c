#include "minishell.h"

void	my_env(t_env *env)
{
	size_t i;

	i = 0;
	while (env->g_env_var[i] != NULL)
	{
		ft_putendl(env->g_env_var[i]);
		i++;
	}
}