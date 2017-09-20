#include "minishell.h"

void	child_signal(int code)
{
	(void)code;
	ft_putchar('\n');
}

void	parent_signal(int code)
{
	(void)code;
	ft_putchar('\n');
	print_prompt(NULL);
}