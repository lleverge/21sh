/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_compl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 19:50:57 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/31 13:41:15 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <cmd_edit.h>

static int		*singlet_signal(int *flag, int mode)
{
	static int	*value;

	if (!mode)
		value = flag;
	else
		flag = value;
	return (value);
}

static void		small_handler(int signal)
{
	int			*flag;
	t_ult		*ult;

	if (signal != SIGINT)
		return ;
	flag = NULL;
	flag = singlet_signal(flag, 1);
	*flag = 0;
	ult = NULL;
	ult = stock_ult(ult, 1);
	term_setup(ult, 0);
	tputs(tgetstr("up", NULL), 1, ft_putchar_int);
}

static int		read_buff(t_compl *list, t_prompt *prompt, char buffer[4])
{
	if (T_LEFT)
		select_prev(list);
	if (T_RIGHT || T_TAB)
		select_next(list);
	if (buffer[0] == 10 && buffer[1] == 0)
	{
		do_selection(list, prompt);
		return (1);
	}
	if (buffer[0] == 27 && !buffer[1])
		return (1);
	return (0);
}

void			read_compl(t_compl *list, t_prompt *prompt)
{
	char		buffer[4];
	int			ret;
	int			flag;

	ft_bzero(buffer, 4);
	print_options(list);
	flag = 1;
	singlet_signal(&flag, 0);
	signal(SIGINT, &small_handler);
	while ((ret = read(0, buffer, 4)) != -1 && flag)
	{
		clr_screen(list);
		if (read_buff(list, prompt, buffer))
			break ;
		print_options(list);
		ft_bzero(buffer, 4);
	}
	main_signal_handler();
}
