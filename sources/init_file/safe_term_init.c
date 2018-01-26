/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_term_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:32:22 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/26 12:51:30 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

void	safe_term_boot(void)
{
	if (tgetent(NULL, "xterm-256color") <= 0)
	{
		ft_putendl_fd("21sh : unable to load terminfo database with assumed\
			value (xterm-256color)", 2);
		exit(1);
	}
	tcaps_check();
}

void	tcaps_check(void)
{
	if (!tgetstr("up", NULL) || !tgetstr("cr", NULL) || !tgetstr("cd", NULL)
		|| !tgetstr("vi", NULL) || !tgetstr("mr", NULL) ||
		!tgetstr("me", NULL))
	{
		ft_putendl_fd("21sh : one or more of used tcaps string missing, \
abort.", 2);
		exit(1);
	}
}
