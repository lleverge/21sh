/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:38:28 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:45:37 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

char		*ft_strinsert_at(char *str, char c, size_t pos)
{
	char	*ret;

	if (!(ret = (char *)malloc(sizeof(char) * ft_strlen(str) + 2)))
	{
		ft_putendl_fd("error: strinsert malloc failed", 2);
		exit(-1);
	}
	ft_strncpy(ret, str, pos);
	ret[pos] = c;
	ft_strcpy(&ret[pos + 1], &str[pos]);
	return (ret);
}

void		putchar_move_curs(t_edit *ed)
{
	if (ed->input->curs->x + 1 <= ed->termi->ws.ws_col)
		ed->input->curs->x++;
	else
	{
		use_cap("do");
		use_cap("cr");
		ed->input->curs->x = 0;
		ed->input->curs->y++;
	}
}

void		insert_rec(t_edit *ed, int y, char *buffer, int rec)
{
	if (line_full(ed, ft_strlen(buffer), y, ed->input->lprom))
	{
		use_ncap("do", rec);
		ft_putchar(buffer[cursor_to_sbuffer(ed, ed->termi->ws.ws_col, y)
						- ed->input->lprom]);
		use_ncap("up", rec);
		use_cap("cr");
		use_ncap("nd", ed->input->curs->x - 1);
		insert_rec(ed, y + 1, buffer, rec + 1);
	}
}

char		*insert_at(t_edit *ed, char *buffer, char c)
{
	insert_rec(ed, ed->input->curs->y, buffer, 0);
	buffer = ft_strinsert_at(buffer, c,
							cursor_to_sbuffer(ed, ed->input->curs->x,
											ed->input->curs->y)
							- ed->input->lprom);
	ft_putchar(c);
	putchar_move_curs(ed);
	return (buffer);
}
