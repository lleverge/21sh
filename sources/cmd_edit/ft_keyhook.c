/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:18:48 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:40:29 by lleverge         ###   ########.fr       */
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

void			move_left(t_edit *ed)
{
	if (ed->input->curs->x > ed->input->lprom)
	{
		ed->input->curs->x -= 1;
		use_cap("le");
	}
}

void			move_down(t_edit *ed)
{
	size_t	len;

	len = ft_strlen(ed->input->cmd_line) + ed->input->lprom;
	if (cursor_to_sbuffer(ed, ed->input->curs->x,
						ed->input->curs->y + 1) < (int)len)
	{
		ed->input->curs->y++;
		use_cap("do");
		use_ncap("nd", ed->input->curs->x - 1);
	}
	else
	{
		if (ed->input->curs->y + 1 == (int)(len - 1)
			/ (ed->termi->ws.ws_col + 1))
		{
			use_cap("do");
			use_cap("cr");
			ed->input->curs->y++;
			use_ncap("nd", (len - 1) % (ed->termi->ws.ws_col + 1));
			ed->input->curs->x = (len - 1) % (ed->termi->ws.ws_col + 1) + 1;
		}
	}
}

void			move_up(t_edit *ed)
{
	if (ed->input->curs->y - 1 >= 0)
	{
		use_cap("up");
		ed->input->curs->y--;
	}
	if (ed->input->curs->x <= ed->input->lprom && ed->input->curs->y == 0)
	{
		ed->input->curs->x = 0;
		use_cap("cr");
		use_ncap("nd", ed->input->lprom - 1);
		ed->input->curs->x = ed->input->lprom;
	}
}
