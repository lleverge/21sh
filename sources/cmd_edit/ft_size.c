/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:51:24 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 19:04:18 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void			get_ws(t_ult *ult)
{
	if (ioctl(ult->term->fd, TIOCGWINSZ, &ult->term->ws) == -1)
	{
		ft_putendl_fd("Ioctl error", 2);
		exit(-1);
	}
	ult->term->ws.ws_col--;
	ult->term->ws.ws_row--;
}
