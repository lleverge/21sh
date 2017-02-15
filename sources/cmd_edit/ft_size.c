/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:51:24 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 18:46:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void			get_ws(t_term *termi)
{
	if (ioctl(termi->fd, TIOCGWINSZ, &termi->ws) == -1)
	{
		ft_putendl_fd("Ioctl error", 2);
		exit(-1);
	}
	termi->ws.ws_col--;
	termi->ws.ws_row--;
}
