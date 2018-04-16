/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:20:35 by lleverge          #+#    #+#             */
/*   Updated: 2018/04/16 15:01:10 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"

t_prompt		*stock_prompt(t_prompt *prompt, int i)
{
	static t_prompt *tmp = NULL;

	if (i == 0)
		tmp = prompt;
	return (tmp);
}

t_prompt		*init_prompt(void)
{
	t_prompt		*prompt;
	struct winsize	win;
	t_ult			*ult;

	ult = NULL;
	ult = stock_ult(ult, 1);
	if (!(prompt = (t_prompt *)malloc(sizeof(t_prompt))))
	{
		ft_putendl_fd("21sh: prompt malloc failed", 2);
		exit_term(ult->term);
		exit(3);
	}
	ft_bzero(prompt->cmd, 2000);
	prompt->i = 0;
	prompt->y = 0;
	prompt->copy_mode = 0;
	prompt->cursor_start = 0;
	prompt->cursor_end = 0;
	prompt->copy_str = NULL;
	ioctl(0, TIOCGWINSZ, &win);
	prompt->win_size = win.ws_col;
	prompt->heredoc = 0;
	return (prompt);
}
