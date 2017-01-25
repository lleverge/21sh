/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:58:42 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 15:28:52 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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
	else
		ft_putstr("empty env\n");
}
