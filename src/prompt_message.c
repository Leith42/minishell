#include "minishell.h"

void	print_prompt(t_env *e)
{
	char buffer[PATH_MAX];
	char *current;

	if ((getcwd(buffer, PATH_MAX)) != NULL)
	{
		current = ft_strrchr(buffer, '/');
		if (current[1] != '\0')
			current++;
		ft_printf("{GREEN}%s{EOC} ", ft_strequ(buffer, e->home) ? "~" : current);
	}
	ft_putstr(PROMPT_MSG);
}