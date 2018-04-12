/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:58:42 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/12 16:11:14 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/cmd_edit.h"

void		print_list(t_env *env)
{
	if (env)
	{
		while (env)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			if (env->content)
				ft_putstr(env->content);
			ft_putchar('\n');
			env = env->next;
		}
	}
}
