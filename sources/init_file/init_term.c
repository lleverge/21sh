/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:47:19 by lleverge          #+#    #+#             */
/*   Updated: 2017/02/09 18:56:10 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

void		init_term2(t_term *termi)
{
	termi->termios.c_lflag &= ~(ICANON);
	termi->termios.c_lflag &= ~(ECHO);
	termi->termios.c_cc[VMIN] = 1;
	termi->termios.c_cc[VTIME] = 0;
	if (tcsetattr(termi->fd, TCSANOW, &(termi->termios)) == -1)
		ft_putendl_fd("error: tcsetattr", 2);
}

t_term		*init_term(void)
{
	char	*name;
	t_term	*termi;

	name = NULL;
	if (!isatty(0))
		ft_putendl_fd("error: isatty", 2);
	if (!(termi = (t_term *)malloc(sizeof(t_term))))
		return (NULL);
	if ((termi->fd = open(ttyname(0), O_RDWR)) == -1)
		ft_putendl_fd("error: tyyname", 2);
	ft_strdel(&name);
	if (tgetent(NULL, getenv("TERMI")) < 1)
		ft_putendl_fd("error: tgetent", 2);
	if (tcgetattr(termi->fd, &(termi->termios)) == -1)
		ft_putendl_fd("error: tcgetattr", 2);
	init_term2(termi);
	return (termi);
}
