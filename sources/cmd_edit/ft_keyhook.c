/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:18:48 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 15:09:17 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"

static void		move_right(void)
{
	use_cap("nd");
}

static void		move_left(void)
{
	use_cap("le");
}

static void		manage_key(char *buffer[5])
{
	if (BUFFER == RIGHT_KEY)
		move_right();
	if (BUFFER == LEFT_KEY)
		move_left();
}

int				ft_keyspot(void)
{
	char	*buffer[5];
	char	*line;

	ft_bzero(buffer, 5);
	line = ft_strdup("");
	while (BUFFER != RET_KEY)
	{
		read(0, buffer, 4);
		manage_key(buffer);
	}
	return (0);
}
