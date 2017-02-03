/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:18:48 by lleverge          #+#    #+#             */
/*   Updated: 2017/01/25 19:38:38 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"

static void		move_right(void)
{
	use_cap("nd");
}

static void		manage_key(char *buffer[5])
{
	if (BUFFER == RIGHT_KEY)
		move_right();
}

int				ft_keyspot(void)
{
	char	*buffer[5];

	ft_bzero(buffer, 5);
	read(0, buffer, 4);
	manage_key(buffer);
	return (0);
}
