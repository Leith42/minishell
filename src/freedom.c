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
	t_list *t;

	if (env == NULL)
		return ;
	free_str_array(env->stdin);
	free(env->home);
	while (env->path)
	{
		t = env->path->next;
		free(env->path->content);
		free(env->path);
		env->path = t;
	}
	free(env);
}