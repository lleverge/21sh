/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:18:48 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 15:45:36 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static void		move_right(t_ult *ult)
{
	ult->curs->x += 1;
	use_cap("nd");
}

static void		move_left(t_ult *ult)
{
	if (ult->curs->x > ult->prom->len)
	{
		ult->curs->x -= 1;
		use_cap("le");
	}
}

static void		manage_key(t_ult *ult, char *buffer[5])
{
	if (BUFFER == RIGHT_KEY)
		move_right(ult);
	if (BUFFER == LEFT_KEY)
		move_left(ult);
}

int				ft_keyspot(t_ult *ult)
{
	char	*buffer[5];

	ft_bzero(buffer, 5);
	while (BUFFER != RET_KEY)
	{
		read(0, buffer, 4);
		manage_key(ult, buffer);
	}
	return (0);
}
