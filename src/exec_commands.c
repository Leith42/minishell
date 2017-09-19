#include "minishell.h"

static int execute(char *cmd_path, char **cmd_with_args)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		execve(cmd_path, cmd_with_args, g_env_var);
	}
	else if (pid < 0)
	{
		print_error("Fork failed to create a child process.");
	}
	wait(&pid);
	return (true);
}

static int check_execution(char *cmd_path, char **cmd_with_args, struct stat cmd_stat)
{
	if (cmd_stat.st_mode & S_IFREG)
	{
		if (cmd_stat.st_mode & S_IXUSR)
		{
			execute(cmd_path, cmd_with_args);
		}
	}
	ft_strdel(&cmd_path);
	return (true);
}

static int check_if_bin(t_list *path, char **cmd_with_args)
{
	char		*join_cmd_path;
	char		*join_slash_path;
	struct stat	s;

	join_cmd_path = NULL;
	while (path != NULL)
	{
		if ((join_slash_path = ft_strjoin(path->content, "/")) == NULL
			|| (join_cmd_path = ft_strjoin(join_slash_path, cmd_with_args[0])) == NULL)
		{
			exit(EXIT_FAILURE);
		}
		ft_strdel(&join_slash_path);
		if (lstat(join_cmd_path, &s) == ERROR)
			ft_strdel(&join_cmd_path);
		else
			return (check_execution(join_cmd_path, cmd_with_args, s));
		path = path->next;
	}
	ft_strdel(&join_cmd_path);
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
		my_echo(cmd_with_args + 1);
	else if (ft_strequ(cmd_with_args[0], ENV) == true)
		my_env();
	else if (ft_strequ(cmd_with_args[0], EXIT) == true)
	{
		free_str_array(cmd_with_args);
		exit_minishell(env, EXIT_SUCCESS);
	}
	else
		return (false);
	return (true);
}

static int check_if_path(char **cmd_with_args)
{
	struct stat		s;

	if (lstat(cmd_with_args[0], &s) != ERROR)
	{
		if (s.st_mode & S_IFDIR)
		{
			puts("dir loul");
			return (true);
		}
	}
	return (false);
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
			if ((cmd_with_args = ft_strsplit(env->stdin[i], ' ')) == NULL)
				exit(EXIT_FAILURE);
			if (check_if_builtin(cmd_with_args, env) == false
				&& check_if_bin(env->path, cmd_with_args) == false
				&& check_if_path(cmd_with_args) == false)
			{
				ft_printf("minishell: command not found: %s\n", cmd_with_args[0]);
			}
			free_str_array(cmd_with_args);
		}
		i++;
	}
	return (true);
}