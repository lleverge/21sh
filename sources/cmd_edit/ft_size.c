/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:51:24 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/15 16:50:37 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

void			get_ws(int fd, t_winsize ws)
{
	if (ioctl(fd, TIOCGWINSZ, &ws) == -1)
	{
		ft_putendl_fd("Ioctl error", 2);
		exit(-1);
	}
	ws.ws_col--;
	ws.ws_row--;
}
