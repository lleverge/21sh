/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfword.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 09:15:27 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/01 12:39:19 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

char			*ft_strpbrk(const char *s1, const char *s2)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = (char*)s1 + ft_strlen(s1) - 1;
	while (s2[i])
	{
		tmp = ft_strchr(s1, (int)s2[i]);
		if (tmp != NULL)
		{
			if (tmp < ret)
				ret = tmp;
		}
		i++;
	}
	if (ret == (char*)s1 + ft_strlen(s1) - 1)
		return (NULL);
	return (ret + 1);
}

static void		move_fword(t_cursor new_cur, t_cursor *cursor)
{
	use_cap("cr");
	use_ncap("do", new_cur.y - cursor->y - 1);
	use_ncap("nd", new_cur.x - 1);
	cursor->x = new_cur.x;
	cursor->y = new_cur.y;
}

void			fword(t_edit *ed)
{
	char		*pos;
	char		*new_pos;
	int			len;
	t_cursor	new_cur;

	len = cursor_to_sbuffer(ed, ed->input->curs->x, ed->input->curs->y) \
		- ed->input->lprom;
	pos = &ed->input->cmd_line[len];
	new_pos = ft_strpbrk(pos, "\t ");
	if (new_pos == NULL)
	{
		end(ed);
		return ;
	}
	while (*new_pos && (*new_pos == '\t' || *new_pos == ' '))
		new_pos++;
	len += new_pos - pos;
	buffer_to_cursor(ed, len + ed->input->lprom, &new_cur);
	move_fword(new_cur, ed->input->curs);
}

static void		move_bword(t_cursor new_cur, t_cursor *cursor)
{
	use_cap("cr");
	use_ncap("up", cursor->y - new_cur.y - 1);
	use_ncap("nd", new_cur.x - 1);
	cursor->x = new_cur.x;
	cursor->y = new_cur.y;
}

void			bword(t_edit *ed)
{
	char		*cp;
	int			len;
	char		*new_pos;
	t_cursor	new_cur;

	len = cursor_to_sbuffer(ed, ed->input->curs->x,
							ed->input->curs->y) - ed->input->lprom;
	while (len >= 1 && (ed->input->cmd_line[len - 1] == '\t'\
						|| ed->input->cmd_line[len - 1] == ' '))
		len--;
	cp = ft_strsub(ed->input->cmd_line, 0, len);
	new_pos = ft_strrpbrk(cp, "\t ");
	buffer_to_cursor(ed, len - (&cp[len] - new_pos)
					+ ed->input->lprom, &new_cur);
	move_bword(new_cur, ed->input->curs);
	free(cp);
}
