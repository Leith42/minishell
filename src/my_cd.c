/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:46:56 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 11:53:02 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_oldpwd_var(char *old_pwd, t_env *env)
{
	char	*join;
	size_t	line;

	line = 0;
	while (env->env_var[line])
	{
		if ((ft_strnequ("OLDPWD=", env->env_var[line], 7)) == true)
			break ;
		line++;
	}
	if (env->env_var[line] != NULL)
	{
		if ((join = ft_strjoin("OLDPWD=", old_pwd)) == NULL)
			exit_minishell(env, EXIT_FAILURE);
		ft_strdel(&env->env_var[line]);
		env->env_var[line] = join;
	}
}

static int	change_working_dir(char *new_path, char *working_dir, t_env *env)
{
	if (chdir(new_path) == ERROR)
	{
		if (access(new_path, F_OK) == -1)
			ft_printf("cd: no such file or directory: %s\n", new_path);
		else if (access(new_path, R_OK) == -1)
			ft_printf("cd: permission denied: %s\n", new_path);
		else
			ft_printf("cd: not a directory: %s\n", new_path);
		return (false);
	}
	change_oldpwd_var(working_dir, env);
	return (true);
}

int			my_cd(t_env *env, char **args)
{
	char buffer[PATH_MAX];
	char *path;

	if ((getcwd(buffer, PATH_MAX)) == NULL)
		exit_minishell(env, EXIT_FAILURE);
	if ((args[0] == NULL || args[0][0] == '~'))
	{
		if ((path = get_home(env)) == NULL)
			return (false);
		return (change_working_dir(path, buffer, env));
	}
	else if ((args[0][0]) == '-')
	{
		if ((path = get_old_pwd(env)) == NULL)
			return (false);
		ft_putendl(path);
		return (change_working_dir(path, buffer, env));
	}
	else
	{
		return (change_working_dir(args[0], buffer, env));
	}
}
