/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:12:52 by vfrolich          #+#    #+#             */
/*   Updated: 2018/01/12 19:02:10 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <lexer.h>
#include <cmd_edit.h>

void	intsig_handler(t_ult *ult, t_prompt *prompt)
{
	struct winsize	win;

	if (prompt->win_size == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		ioctl(0, TIOCGWINSZ, &win);
		prompt->win_size = win.ws_col;
	}
	prompt_print(prompt, 0);
	reset_prompt(prompt);
	ft_strdel(&ult->cmd);
	prompt->i = 0;
}

void	signal_dispatch(int signal)
{
	t_ult			*ult;
	t_prompt		*prompt;

	ult = NULL;
	prompt = NULL;
	ult = stock_ult(ult, 1);
	prompt = stock_prompt(prompt, 1);
	if (signal == SIGINT)
		intsig_handler(ult, prompt);
}

void	main_signal_handler(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = &signal_dispatch;
	if (sigaction(SIGINT, &action, NULL) == -1)
		ft_putendl_fd("21sh : sigaction error", 2);
}
