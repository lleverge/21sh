/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:12:52 by vfrolich          #+#    #+#             */
/*   Updated: 2018/03/15 19:36:30 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>
#include <lexer.h>
#include <cmd_edit.h>

static void full_lines(t_prompt *prompt)
{
	int		count;

	count = prompt->i;
	if ((size_t)prompt->i == (prompt->win_size - 3))
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	else if ((size_t)prompt->i > (prompt->win_size - 3))
	{
		count -= (prompt->win_size - 3);
		if ((size_t)count == prompt->win_size)
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		while ((size_t)count >= prompt->win_size)
		{
			count -= prompt->win_size;
			if ((size_t)count == prompt->win_size)
				tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		}
	}
}

void	sigwinch_handler(t_prompt *prompt)
{
	
	reset(prompt);
	prompt_print(prompt, 1);
}

void	intsig_handler(t_prompt *prompt, t_ult *ult)
{
	struct winsize	win;

	if (prompt->win_size == 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		ioctl(0, TIOCGWINSZ, &win);
		prompt->win_size = win.ws_col;
	}
	full_lines(prompt);
	prompt_print(prompt, 0);
	ft_putchar('\n');
	get_prompt(ult->env);
	ft_strclr(prompt->cmd);
	ft_strdel(&ult->cmd);
	prompt->i = 0;
	prompt_print(prompt, 1);
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
		intsig_handler(prompt, ult);
	if (signal == SIGWINCH)
		sigwinch_handler(prompt);
}

void	main_signal_handler(void)
{
	signal(SIGINT, &signal_dispatch);
	signal(SIGWINCH, &signal_dispatch);
	signal(SIGTSTP, SIG_IGN);
}
