/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:23:12 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/23 18:12:23 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static void			func1_key(t_key *key, t_edit *ed)
{
	int		i;

	i = 0;
	while (i != FUNC1)
	{
		(*(key->func1)[i])(ed);
		i++;
	}
}

static void			handle_char(t_edit *ed, char c)
{
	char	*tmp;

	tmp = insert_at(ed, ed->input->cmd_line, c);
	free(ed->input->cmd_line);
	ed->input->cmd_line = tmp;
}

static char			*line_edit1(char *buffer)
{
	ft_memset(buffer, '\0', 7);
	read(0, buffer, 7);
	return (buffer);
}

static void			line_edit2(char *buffer, t_edit *ed)
{
	if (ft_isprint(buffer[0]) && ft_strlen(buffer) == 1 &&
		ft_strlen(ed->input->cmd_line) < 600 &&
		ft_cntc(ed->input->cmd_line, '\n') == 0)
		handle_char(ed, buffer[0]);
}

void				line_edition(t_key *key, t_edit *ed)
{
	char		*buffer;

	buffer = key->buffer;
	while (42)
	{
		buffer = line_edit1(buffer);
		func1_key(key, ed);
		line_edit2(buffer, ed);
		if (buffer[0] == T_ENTER && buffer[1] == 0)
			break ;
	}
}
