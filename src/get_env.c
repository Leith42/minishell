/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:50:18 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 11:52:45 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_path(t_env *env)
{
	size_t	y;
	char	**paths;
	char	*tmp;

	y = 0;
	while (env->env_var[y] && ft_strnequ("PATH=", env->env_var[y], 5) == false)
	{
		y++;
	}
	if (env->env_var[y] == NULL || \
		(paths = ft_strsplit(env->env_var[y] + 5, ':')) == NULL)
		return (NULL);
	y = 0;
	while (paths[y])
	{
		if ((tmp = ft_strjoin(paths[y], "/")) == NULL)
			return (NULL);
		free(paths[y]);
		paths[y] = tmp;
		y++;
	}
	return (paths);
}

char		*get_old_pwd(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->env_var[i] != NULL)
	{
		if (ft_strnequ("OLDPWD=", env->env_var[i], 7) == true)
		{
			return (env->env_var[i] + 7);
		}
		i++;
	}
	return (NULL);
}

char		*get_home(t_env *env)
{
	size_t	i;

	i = 0;
	if (env->env_var == NULL)
		return (NULL);
	while (env->env_var[i] != NULL)
	{
		if (ft_strnequ("HOME=", env->env_var[i], 5) == true)
		{
			return (env->env_var[i] + 5);
		}
		i++;
	}
	return (NULL);
}

static void	fill_genv(t_env *e, char **env)
{
	size_t i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	if ((e->env_var = ft_memalloc(sizeof(char *) * (i + 1))) == NULL)
	{
		exit_minishell(e, EXIT_FAILURE);
	}
	i = 0;
	while (env[i] != NULL)
	{
		if ((e->env_var[i] = ft_strdup(env[i])) == NULL)
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
	fill_genv(e, env);
	return (e);
}
