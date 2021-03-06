/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:46:01 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 12:15:29 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		get_var_line(char *var, t_env *env)
{
	size_t	i;
	size_t	var_len;

	if (var == NULL)
		exit_minishell(env, EXIT_FAILURE);
	i = 0;
	var_len = ft_strlen(var);
	while (env->env_var[i] != NULL)
	{
		if ((ft_strnequ(var, env->env_var[i], var_len)) == true)
			break ;
		i++;
	}
	ft_strdel(&var);
	return (i);
}

static int	new_and_cpy(size_t size, char *variable, t_env *env)
{
	size_t	i;
	char	**new;

	if ((new = ft_memalloc(sizeof(char *) * (size))) == NULL)
		return (ERROR);
	i = 0;
	while (env->env_var[i] != NULL)
	{
		if ((new[i] = ft_strdup(env->env_var[i])) == NULL)
			return (ERROR);
		ft_strdel(&env->env_var[i]);
		i++;
	}
	new[i] = variable;
	free(env->env_var);
	env->env_var = new;
	return (true);
}

void		add_new_var(size_t line, char **args, t_env *env)
{
	char *name;
	char *name_and_value;

	name_and_value = NULL;
	name = ft_strjoin(args[0], "=");
	if ((args[1][0] == '"') && (args[1][ft_strlen(args[1]) - 1]) == '"')
	{
		if (name == NULL || \
			(name_and_value = ft_strjoin(name, args[1] + 1)) == NULL)
			exit_minishell(env, EXIT_FAILURE);
		name_and_value[ft_strlen(name_and_value) - 1] = '\0';
	}
	else if (name == NULL || \
		(name_and_value = ft_strjoin(name, args[1])) == NULL)
		exit_minishell(env, EXIT_FAILURE);
	ft_strdel(&name);
	if (env->env_var[line] != NULL)
	{
		ft_strdel(&env->env_var[line]);
		env->env_var[line] = name_and_value;
	}
	else if ((new_and_cpy(line + 2, name_and_value, env)) == ERROR)
		exit_minishell(env, EXIT_FAILURE);
}

int			my_setenv(t_env *env, char **args)
{
	size_t line;

	if ((args[0] == NULL) || (args[1] == NULL) || (args[2] != NULL))
	{
		print_error("setenv: invalid number of arguments.");
		print_error("usage: setenv [name] [value]");
		return (false);
	}
	line = get_var_line(ft_strjoin(args[0], "="), env);
	add_new_var(line, args, env);
	return (true);
}
