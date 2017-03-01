/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   homend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 09:11:07 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:41:02 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void	home(t_edit *ed)
{
	use_ncap("up", ed->input->curs->y - 1);
	use_cap("cr");
	use_ncap("nd", ed->input->lprom - 1);
	ed->input->curs->x = ed->input->lprom;
	ed->input->curs->y = 0;
}

void	end(t_edit *ed)
{
	t_cursor	new_cur;

	buffer_to_cursor(ed, ft_strlen(ed->input->cmd_line)
					+ ed->input->lprom, &new_cur);
	use_cap("cr");
	use_ncap("do", new_cur.y - 1 - ed->input->curs->y);
	use_ncap("nd", new_cur.x - 1);
	ed->input->curs->x = new_cur.x;
	ed->input->curs->y = new_cur.y;
}
