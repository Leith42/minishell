#include "minishell.h"

int ignore_command(char *cmd)
{
	size_t i;

	i = 0;
	if (cmd == NULL)
		return (false);
	while (cmd[i])
	{
		if (cmd[i] > 0x20)
			return (false);
		i++;
	}
	return (true);
}