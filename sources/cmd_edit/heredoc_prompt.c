/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:40:55 by vfrolich          #+#    #+#             */
/*   Updated: 2018/04/12 15:44:27 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd_edit.h"

void			reset_prompt_heredoc(t_prompt *prompt, int show_cursor)
{
	size_t		i;
	size_t		j;

	j = 3;
	i = 0;
	prompt->y = 0;
	if (show_cursor)
		tputs(tgetstr("vi", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	while (i < ft_strlen(prompt->cmd))
	{
		if (j >= prompt->win_size)
		{
			tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
			j = 0;
		}
		j++;
		i++;
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	ft_putstr("> ");
}
