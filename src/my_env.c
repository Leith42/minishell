/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:46:45 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 11:46:46 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_env(t_env *env)
{
	size_t i;

	i = 0;
	while (env->env_var[i] != NULL)
	{
		ft_putendl(env->env_var[i]);
		i++;
	}
}
