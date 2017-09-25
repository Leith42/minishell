/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:17:24 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 12:17:25 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_var(size_t line, t_env *env)
{
	char	**new;
	size_t	i;
	size_t	n;

	i = 0;
	while (env->env_var[i] != NULL)
		i++;
	if ((new = ft_memalloc(sizeof(char *) * (i + 2))) == NULL)
		exit_minishell(env, EXIT_FAILURE);
	i = 0;
	n = 0;
	while (env->env_var[i] != NULL)
	{
		if (i != line)
		{
			if ((new[n] = ft_strdup(env->env_var[i])) == NULL)
				exit_minishell(env, EXIT_FAILURE);
			n++;
		}
		ft_strdel(&env->env_var[i]);
		i++;
	}
	free(env->env_var);
	env->env_var = new;
}

int			my_unsetenv(t_env *env, char **args)
{
	size_t	line;

	if (args[0] == NULL || args[1] != NULL)
	{
		print_error("unsetenv: invalid number of arguments.");
		print_error("usage: unsetenv [name]");
		return (false);
	}
	line = get_var_line(ft_strjoin(args[0], "="), env);
	if (env->env_var[line] == NULL)
	{
		print_error("unsetenv: environment variable not found.");
		return (false);
	}
	del_var(line, env);
	return (true);
}
