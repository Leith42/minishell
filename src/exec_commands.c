#include "minishell.h"

static int execute(char *cmd_path, char **cmd_with_args, t_env *env)
{
	pid_t	pid;

	signal(SIGINT, child_signal);
	if ((pid = fork()) == 0)
	{
		execve(cmd_path, cmd_with_args, env->env_var);
	}
	else if (pid < 0)
	{
		print_error("Fork failed to create a child process.");
		return (false);
	}
	wait(&pid);
	return (true);
}

static int check_if_bin(char **path, char **cmd_with_args, t_env *env)
{
	char		*cmd_path;
	struct stat	s;
	size_t 		i;

	i = 0;
	cmd_path = NULL;
	if (path == NULL)
		return (false);
	while (path[i] != NULL)
	{
		if ((cmd_path = ft_strjoin(path[i], cmd_with_args[0])) == NULL)
		{
			exit_minishell(env, EXIT_FAILURE);
		}
		if (lstat(cmd_path, &s) != ERROR && s.st_mode & S_IFREG && s.st_mode & S_IXUSR)
		{
			free_str_array(path);
			execute(cmd_path, cmd_with_args, env);
			ft_strdel(&cmd_path);
			return (true);
		}
		ft_strdel(&cmd_path);
		i++;
	}
	ft_strdel(&cmd_path);
	free_str_array(path);
	return (false);
}

static int check_if_path(char **cmd_with_args, t_env *env)
{
	char			*home;
	struct stat		s;

	if (ft_strequ(cmd_with_args[0], "~") == true)
	{
		if ((home = ft_strdup(get_home(env))) == NULL)
			return (true);
		ft_strdel(&cmd_with_args[0]);
		cmd_with_args[0] = home;
	}
	if (lstat(cmd_with_args[0], &s) != ERROR)
	{
		if (s.st_mode & S_IFDIR)
		{
			return (my_cd(env, cmd_with_args));
		}
		else if (s.st_mode & S_IFREG && s.st_mode & S_IXUSR)
		{
			return (execute(cmd_with_args[0], cmd_with_args, env));
		}
	}
	return (false);
}

static int check_if_builtin(char **cmd_with_args, t_env *env)
{
	if (ft_strequ(cmd_with_args[0], CD) == true)
		my_cd(env, cmd_with_args + 1);
	else if (ft_strequ(cmd_with_args[0], SETENV) == true)
		my_setenv(env, cmd_with_args + 1);
	else if (ft_strequ(cmd_with_args[0], UNSETENV) == true)
		my_unsetenv(env, cmd_with_args + 1);
	else if (ft_strequ(cmd_with_args[0], ECHO) == true)
		my_echo(cmd_with_args + 1, env);
	else if (ft_strequ(cmd_with_args[0], ENV) == true)
		my_env(env);
	else if (ft_strequ(cmd_with_args[0], EXIT) == true)
	{
		free_str_array(cmd_with_args);
		exit_minishell(env, EXIT_SUCCESS);
	}
	else
		return (false);
	return (true);
}

int 	exec_commands(t_env *env)
{
	unsigned int	i;
	char			**cmd_with_args;

	i = 0;
	while (env->stdin[i] != NULL)
	{
		if (ignore_command(env->stdin[i]) == false)
		{
			replace_tabs_by_spaces(env->stdin[i]);
			if ((cmd_with_args = ft_strsplit(env->stdin[i], ' ')) == NULL)
				exit_minishell(env, EXIT_FAILURE);
			trim_str_array(cmd_with_args, env);
			if (check_if_builtin(cmd_with_args, env) == false
				&& check_if_bin(get_path(env), cmd_with_args, env) == false
				&& check_if_path(cmd_with_args, env) == false)
			{
				ft_printf("minishell: command not found: %s\n", cmd_with_args[0]);
			}
			free_str_array(cmd_with_args);
		}
		i++;
	}
	return (true);
}
