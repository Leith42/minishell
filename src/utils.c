/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:45:45 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 11:45:54 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_tabs_by_spaces(char *str)
{
	size_t i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

void	trim_str_array(char **arr, t_env *env)
{
	size_t	i;
	char	*trim;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		if ((trim = ft_strtrim(arr[i])) == NULL)
			exit_minishell(env, EXIT_FAILURE);
		ft_strdel(&arr[i]);
		arr[i] = trim;
		i++;
	}
}

int		ignore_command(char *cmd)
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
