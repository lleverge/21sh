/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:51:24 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/23 15:06:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <shell.h>

int			cursor_to_sbuffer(t_edit *ed, int x, int y)
{
	return (x + y * (ed->termi->ws.ws_col + 1));
}

void		buffer_to_cursor(t_edit *ed, int pos, t_cursor *cursor)
{
	cursor->y = pos / (ed->termi->ws.ws_col + 1);
	cursor->x = pos % (ed->termi->ws.ws_col + 1);
}

int			line_full(t_edit *ed, int len, int y, int prompt_size)
{
	int		nlen;

	nlen = ed->termi->ws.ws_col + y * (ed->termi->ws.ws_col + 1);
	nlen -= prompt_size;
	if (len > nlen)
		return (1);
	return (0);
}

void		get_ws(t_term *termi)
{
	if (ioctl(termi->fd, TIOCGWINSZ, &termi->ws) == -1)
	{
		ft_putendl_fd("Ioctl error", 2);
		exit(-1);
	}
	termi->ws.ws_col--;
	termi->ws.ws_row--;
}
