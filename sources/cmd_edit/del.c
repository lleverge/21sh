/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:30:34 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:48:49 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static void		del_rec(t_edit *ed, int y, char *buffer, int rec)
{
	int			len;

	len = ft_strlen(buffer) + ed->input->lprom;
	if (y < len / (ed->termi->ws.ws_col + 1))
	{
		use_cap("sc");
		use_ncap("do", rec);
		use_cap("dc");
		use_cap("up");
		use_cap("cr");
		use_ncap("nd", ed->termi->ws.ws_col + 1);
		ft_putchar(buffer[cursor_to_sbuffer(ed, 0, y + 1)
						- ed->input->lprom - 1]);
		use_cap("rc");
		del_rec(ed, y + 1, buffer, rec + 1);
	}
}

static void		del_end_of_line(char *cmd_line, t_edit *ed)
{
	ed->input->curs->y--;
	ed->input->curs->x = ed->termi->ws.ws_col;
	use_cap("up");
	use_ncap("nd", ed->termi->ws.ws_col - 1);
	if (check_max(ed, ed->input->curs, cmd_line, 0))
		supress_end(ed);
}

static void		del_basic(t_edit *ed)
{
	ed->input->curs->x--;
	use_cap("le");
	use_cap("dc");
}

void			del(t_edit *ed)
{
	char		*tmp;

	if (ft_strlen(ed->input->cmd_line) == 0 || \
		check_max(ed, ed->input->curs, ed->input->cmd_line, 0))
		return ;
	tmp = ft_strsupress_at(ed->input->cmd_line,
						cursor_to_sbuffer(ed, ed->input->curs->x,
										ed->input->curs->y) - ed->input->lprom);
	free(ed->input->cmd_line);
	if (ed->input->curs->x == ed->termi->ws.ws_col)
		supress_end(ed);
	else
		use_cap("dc");
	if (line_full(ed, ft_strlen(tmp) + ed->input->lprom,
				ed->input->curs->y, ed->input->lprom))
		del_rec(ed, ed->input->curs->y, tmp, 0);
	ed->input->cmd_line = tmp;
}

void			del_at(t_edit *ed)
{
	char		*tmp;

	if (ed->input->curs->x - 1 < ed->input->lprom && ed->input->curs->y == 0)
		return ;
	tmp = ft_strsupress_at(ed->input->cmd_line,
						cursor_to_sbuffer(ed, ed->input->curs->x,
						ed->input->curs->y) - ed->input->lprom - 1);
	free(ed->input->cmd_line);
	if (ed->input->curs->x - 1 < 0)
		del_end_of_line(tmp, ed);
	else
		del_basic(ed);
	if (line_full(ed, ft_strlen(tmp) + ed->input->lprom,
				ed->input->curs->y, ed->input->lprom))
		del_rec(ed, ed->input->curs->y, tmp, 0);
	ed->input->cmd_line = tmp;
}
