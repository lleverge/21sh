/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:49:13 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 17:50:03 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"
#include "../../includes/shell.h"

void		term_setup(t_ult *ult, int value)
{
	ult->term->fd = open(ttyname(0), O_RDWR);
	if (tcgetattr(ult->term->fd, &(ult->term->termios)) == -1)
	{
		ft_putendl("error: tcgetattr");
		return ;
	}
	ult->term->termios.c_cc[VMIN] = value;
	if (tcsetattr(ult->term->fd, TCSANOW, &(ult->term->termios)) == -1)
	{
		ft_putendl_fd("error: tcsetattr", 2);
		return ;
	}
	close(ult->term->fd);
}
