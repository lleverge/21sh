/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:18:48 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 17:04:52 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void			move_right(t_edit *ed)
{
	if (ed->input->curs->x < ed->termi->ws.ws_col)
	{
		ed->input->curs->x += 1;
		use_cap("nd");
		}
}
/*
void			move_left(t_edit *ed)
{
	if (ed->input->curs->x > ed->input->lprom)
	{
		ed->input->curs->x -= 1;
		use_cap("le");
	}
	}*/
/*
static void		manage_key(t_edit *ed, char *buffer[5])
{
	if (BUFFER == RIGHT_KEY)
		move_right(ed);
	if (BUFFER == LEFT_KEY)
		move_left(ed);
}

int				ft_keyspot(t_edit *ed)
{
	char	*buffer[5];

	ft_bzero(buffer, 5);
	while (BUFFER != RET_KEY)
	{
		read(0, buffer, 4);
		manage_key(ed, buffer);
	}
	return (0);
	}*/
