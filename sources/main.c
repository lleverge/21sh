/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:41:06 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/18 13:04:19 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			main(int ac, char **av, char **environ)
{
	t_ult	*ult;

	av = NULL;
	ult = NULL;
	(void)av;
	if (ac != 1)
		ft_putendl_fd("error: 21sh requires no arguments", 2);
	return (0);
}
