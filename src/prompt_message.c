/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:45:13 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 11:45:37 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(t_env *env)
{
	char buffer[PATH_MAX];
	char *current;

	if ((getcwd(buffer, PATH_MAX)) != NULL)
	{
		current = ft_strrchr(buffer, '/');
		if (current[1] != '\0')
			current++;
		if (env)
			ft_printf("{GREEN}%s{EOC} ", \
				ft_strequ(buffer, get_home(env)) ? "~" : current);
		else
			ft_printf("{GREEN}%s{EOC} ", current);
	}
	ft_putstr(PROMPT_MSG);
}
