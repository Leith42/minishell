#include "minishell.h"

static void	get_path(t_env *e, char **env)
{
	size_t			y;
	char			**paths;
	t_list			*new;

	y = 0;
	while (env[y] && ft_strnequ("PATH=", env[y], 5) == false)
		y++;
	if (env[y] == NULL || (paths = ft_strsplit(env[y] + 5, ':')) == NULL)
		exit_minishell(e, EXIT_FAILURE);
	y = 0;
	while (paths[y] != NULL)
	{
		if (e->path == NULL)
		{
			if ((e->path = ft_lstnew(paths[y], ft_strlen(paths[y]))) == NULL)
				exit_minishell(e, EXIT_FAILURE);
		}
		else
		{
			if ((new = ft_lstnew(paths[y], ft_strlen(paths[y]))) == NULL)
				exit_minishell(e, EXIT_FAILURE);
			ft_lstadd(&e->path, new);
		}
		y++;
	}
	free_str_array(paths);
}

static void	get_home(t_env *e, char **env)
{
	size_t y;

	y = 0;
	while (env[y] && ft_strnequ("HOME=", env[y], 5) == false)
	{
		y++;
	}
	if (env[y] == NULL || (e->home = ft_strdup(env[y] + 5)) == NULL)
	{
		exit_minishell(e, EXIT_FAILURE);
	}
}

static void	fill_genv(t_env *e, char **env)
{
	size_t i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	if ((g_env_var = ft_memalloc(sizeof(char *) * (i + 1))) == NULL)
	{
		exit_minishell(e, EXIT_FAILURE);
	}
	i = 0;
	while (env[i] != NULL)
	{
		if ((g_env_var[i] = ft_strdup(env[i])) == NULL)
		{
			exit_minishell(e, EXIT_FAILURE);
		}
		i++;
	}
}

t_env		*get_env(char **env)
{

	t_env *e;

	if ((e = ft_memalloc(sizeof(t_env))) == NULL)
	{
		exit_minishell(e, EXIT_FAILURE);
	}
	get_path(e, env);
	get_home(e, env);
	fill_genv(e, env);
	return (e);
}