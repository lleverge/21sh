/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:20:35 by lleverge          #+#    #+#             */
/*   Updated: 2017/03/08 09:50:36 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd_edit.h>

t_prompt		*stock_prompt(t_prompt *prompt, int i)
{
	static t_prompt *tmp;

	tmp = NULL;
	if (i == 0)
		tmp = prompt;
	return (tmp);
}

t_prompt		*init_prompt(void)
{
	t_prompt		*prompt;
	struct winsize	win;

	if (!(prompt = (t_prompt *)malloc(sizeof(t_prompt))))
		return (NULL);
	ft_bzero(prompt->cmd, 2000);
	prompt->i = 0;
	prompt->y = 0;
	prompt->copy_mode = 0;
	prompt->cursor_start = 0;
	prompt->cursor_end = 0;
	prompt->copy_str = NULL;
	ioctl(0, TIOCGWINSZ, &win);
	prompt->win_size = win.ws_col;
	return (prompt);
}