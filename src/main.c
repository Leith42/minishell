#include "minishell.h"

void	exit_minishell(t_env *env, int exit_code)
{
	free_env(env);
	ft_putchar('\n');
	exit(exit_code);
}

int		get_commands(t_env *env)
{
	int		gnl;
	char	*buf;

	buf = NULL;
	gnl = get_next_line(0, &buf);
	if (gnl > 0)
	{
		if ((env->stdin = ft_strsplit(buf, ';')) == NULL)
			return (ERROR);
		free(buf);
	}
	return (gnl);
}

int		main(int argc, char **argv, char **e)
{
	int		gnl;
	t_env	*env;

	env = get_env(e);
	(void)argc;
	(void)argv;
	while (true)
	{
		signal(SIGINT, parent_signal);
		print_prompt(env);
		if ((gnl = get_commands(env)) > 0)
		{
			trim_str_array(env->stdin, env);
			exec_commands(env);
			free_str_array(env->stdin);
			env->stdin = NULL;
		}
		else
		{
			exit_minishell(env, gnl == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
		}
	}
}
