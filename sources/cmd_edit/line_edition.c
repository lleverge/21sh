/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:23:12 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/16 17:20:14 by lleverge         ###   ########.fr       */
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

static char			*line_edit1(char *buffer)
{
	ft_memset(buffer, '\0', 7);
	read(0, buffer, 7);
	return (buffer);
}

void				line_edition(t_key *key, t_edit *ed)
{
	char		*buffer;

	buffer = key->buffer;
	while (42)
	{
		buffer = line_edit1(buffer);
		func1_key(key, ed);
		if (buffer[0] == T_ENTER && buffer[1] == 0)
			break ;
	}
}
