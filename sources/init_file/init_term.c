/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:47:19 by lleverge          #+#    #+#             */
/*   Updated: 2018/03/23 16:51:44 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

void		exit_eof(t_term *termi, t_prompt *prompt)
{
	prompt_print(prompt, 0);
	reset_term(termi);
	free_prompt(&prompt);
	ft_putchar('\n');
	exit(0);
}

int			reset_term(t_term *termi)
{
	tputs(tgetstr("ve", NULL), 1, ft_putchar_int);
	if (tcgetattr(0, &(termi->termios)) == -1)
	{
		ft_putendl_fd("tcgetattr in reset term failed", 2);
		return (-1);
	}
	termi->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &(termi->termios)) == -1)
	{
		ft_putendl_fd("tcsetattr in reset term failed", 2);
		return (-1);
	}
	return (0);
}

void		exit_term(t_term *termi)
{
	if (tcgetattr(termi->fd, &(termi->termios)) == -1)
	{
		ft_putendl("error: tcgetattr");
		exit(-1);
	}
	termi->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(termi->fd, TCSANOW, &(termi->termios)) == -1)
	{
		ft_putendl("error: tcsetattr");
		exit(-1);
	}
	close(termi->fd);
}

void		init_term2(t_term *termi)
{
	termi->termios.c_lflag &= ~(ICANON);
	termi->termios.c_lflag &= ~(ECHO);
	termi->termios.c_cc[VMIN] = 1;
	termi->termios.c_cc[VTIME] = 1;
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
	if (tgetent(NULL, getenv("TERM")) < 1)
		safe_term_boot();
	tcaps_check();
	if (tcgetattr(termi->fd, &(termi->termios)) == -1)
		ft_putendl_fd("error: tcgetattr", 2);
	init_term2(termi);
	close(termi->fd);
	return (termi);
}
