#include "minishell.h"

int my_echo(char **args)
{
	size_t i;

	i = 0;
	if (args[i] == NULL)
	{
		ft_putchar('\n');
	}
	else
	{
		while (args[i] != NULL)
		{
			if (i > 0)
				ft_putchar(' ');
			if ((args[i][0] == '"') && (args[i][ft_strlen(args[i]) - 1]) == '"')
				ft_putnstr(args[i] + 1, ft_strlen((args[i] + 1)) - 1);
			else
				ft_putstr(args[i]);
			i++;
		}
		ft_putchar('\n');
	}
	return (true);
}