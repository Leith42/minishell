#include "minishell.h"

void	free_str_array(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env(t_env *env)
{
	if (env == NULL)
		return ;
	free_str_array(env->stdin);
	free_str_array(env->env_var);
	free(env);
}

void	free_lst(void *content, size_t n)
{
	if (content != NULL)
		ft_memdel(&content);
	(void)n;
}