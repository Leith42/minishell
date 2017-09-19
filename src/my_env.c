#include "minishell.h"

void	my_env(void)
{
	size_t i;

	i = 0;
	while (g_env_var[i] != NULL)
	{
		ft_putendl(g_env_var[i]);
		i++;
	}
}