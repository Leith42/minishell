/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:45:41 by aazri             #+#    #+#             */
/*   Updated: 2017/09/25 11:45:41 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
