/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:28:04 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 16:23:39 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

t_cursor		*init_cursor(void)
{
	t_cursor		*curs;

	if (!(curs = (t_cursor *)malloc(sizeof(t_cursor))))
	{
		ft_putendl_fd("error: struct curs malloc failed", 2);
		exit(-1);
	}
	curs->x = 0;
	curs->y = 0;
	return (curs);
}
